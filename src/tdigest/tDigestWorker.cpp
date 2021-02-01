#include "tDigestWorker.h"

tDigestWorker::tDigestWorker(int nMaxNumber)
	: m_nMaxNumber(nMaxNumber)
	, m_nIndex(0)
{
	m_pTDigest = std::unique_ptr<TDigest>(new TDigest(100));
	m_pool = std::unique_ptr<double[]>(new double[nMaxNumber]);
}

tDigestWorker::~tDigestWorker(void)
{
}

bool tDigestWorker::addValue( double dValue )
{
	bool bRet = false;
	m_pool[m_nIndex] = dValue;
	m_nIndex++;
	if (m_nIndex == m_nMaxNumber)
	{
		for (int i = 0; i < m_nMaxNumber; i++)
			m_pTDigest->add(m_pool[i]);
		bRet = true;
	}
	return bRet;
}

double tDigestWorker::getQuantile(double dPercentage)
{
	return m_pTDigest->quantile(dPercentage);
}
