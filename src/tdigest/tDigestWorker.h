//#ifndef HEADER_TDIGESTWORKER
//#define HEADER_TDIGESTWORKER
#pragma once
#include <thread>
#include <memory>
#include "tdigest.hpp"

class tDigestWorker
{
public:
	tDigestWorker(int nMaxNumber);
	~tDigestWorker(void);

	bool addValue(double value);
	double getQuantile(double dPercentage);
private:
	std::unique_ptr<TDigest> m_pTDigest;
	int m_nMaxNumber;
	int m_nIndex;
	std::unique_ptr<double[]> m_pool;
};

