#include <iostream>
#include <ctime>
#include <thread>
#include "tDigestWorker.h"
#include <memory>
using namespace std;


int main(int argc, char *argv[])
{
	int nMillion = 6;
	int nThreadSize = 1000;
	int nThreadCalls = nMillion*1000;

	int nSize = nThreadCalls * nThreadSize;
	time_t begin,end;
	double difference = 0.0;

	cout << "Test 1" << endl;
	TDigest* tdigest = new TDigest(100);
	time (&begin);
	for (int i=0; i< nSize; i++)
	{
		tdigest->add(rand() % 1001);
	}
	time (&end);
	difference = difftime (end,begin);
	printf ("Time taken to call TDigest's add function %d million times is %.2lf seconds.\n", nMillion, difference );

	cout << "Test 2" << endl;
	time (&begin);
	for (int i=0; i< nSize; i++)
	{
		tdigest->quantile(0.5);
	}
	time (&end);
	difference = difftime (end,begin);
	printf ("Time taken to call TDigest's quantile function %d million times is %.2lf seconds.\n", nMillion, difference );

	cout << "Test 3" << endl;
	TDigest* tdigest2 = new TDigest(100);
	time (&begin);
	for (int i=0; i< nThreadSize; i++)
	{
		std::thread workerThread([=]{ for(int j=0; j<nThreadCalls; j++) tdigest2->add(rand() % 1001);});
		workerThread.join();
	}
	time (&end);
	difference = difftime (end,begin);
	printf ("Time taken for %d threads to call TDigest's add function %d times is %.2lf seconds.\n", nThreadSize, nThreadCalls, difference );

	cout << "Test 4" << endl;
	time (&begin);
	for (int i=0; i< nThreadSize; i++)
	{
		std::thread workerThread([=]{for(int j=0; j<nThreadCalls; j++) tdigest2->quantile(0.5);});
		workerThread.join();
	}
	time (&end);
	difference = difftime (end,begin);
	printf ("Time taken for %d threads to call TDigest's quantile function %d times is %.2lf seconds.\n", nThreadSize, nThreadCalls, difference );

	cout << "Test 5" << endl;
	auto pWorker = new tDigestWorker(nSize);
	time (&begin);
	std::thread singleWorkerThread([=]{for(int j=0; j<nSize; j++) pWorker->addValue(rand() % 1001);});
	singleWorkerThread.join();
	time (&end);
	difference = difftime (end,begin);
	printf ("Time taken for a single TDigestWorker thread to call addValue function %d million times is %.2lf seconds.\n", nMillion, difference );

	cout << "Test 6" << endl;
	time (&begin);
	std::thread singleWorkerThread2([=]{for(int j=0; j<nSize; j++) pWorker->getQuantile(0.5);});
	singleWorkerThread2.join();
	time (&end);
	difference = difftime(end,begin);
	printf ("Time taken for a single TDigestWorker thread to call getQuantile function %d million times is %.2lf seconds.\n", nMillion, difference );

	cout << "Test 7" << endl;
	auto pMultiThreadWorker = new tDigestWorker(nSize);
	time (&begin);
	for (int i=0; i< nThreadSize; i++)
	{
		std::thread workerThread([=]{for(int j=0; j<nThreadCalls; j++)pMultiThreadWorker ->addValue(rand() % 1001);});
		workerThread.join();
	}
	time (&end);
	difference = difftime(end,begin);
	printf ("Time taken for %d threads to call TDigestWorker addValue function %d times is %.2lf seconds.\n", nThreadSize, nThreadCalls, difference );

	cout << "Test 8" << endl;
	time (&begin);
	for (int i=0; i< nThreadSize; i++)
	{
		std::thread workerThread([=]{for(int j=0; j<nThreadCalls; j++)pMultiThreadWorker ->getQuantile(0.5);});
		workerThread.join();
	}
	time (&end);
	difference = difftime(end,begin);
	printf ("Time taken for %d threads to call TDigestWorker getQuantile function %d times is %.2lf seconds.\n", nThreadSize, nThreadCalls, difference );

	cout << "Please press a key to continue" << endl;
	getchar();
	return EXIT_SUCCESS;
}