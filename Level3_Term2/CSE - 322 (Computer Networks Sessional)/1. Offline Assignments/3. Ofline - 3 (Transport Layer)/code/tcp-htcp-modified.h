#ifndef TCP_HTCP_MODIFIED_H
#define TCP_HTCP_MODIFIED_H

#include "tcp-congestion-ops.h"

namespace ns3
{

class TcpSocketState;

class TcpHtcpModified : public TcpNewReno
{
  public:
    static TypeId GetTypeId();
    TcpHtcpModified();
    TcpHtcpModified(const TcpHtcpModified& sock);
    ~TcpHtcpModified() override;
    std::string GetName() const override;
    Ptr<TcpCongestionOps> Fork() override;
    uint32_t GetSsThresh(Ptr<const TcpSocketState> tcb, uint32_t bytesInFlight) override;
    void PktsAcked(Ptr<TcpSocketState> tcb, uint32_t segmentsAcked, const Time& rtt) override;

  protected:
    void CongestionAvoidance(Ptr<TcpSocketState> tcb, uint32_t segmentsAcked) override;

  private:
    void UpdateAlpha();
    void UpdateBeta();

    double m_alpha;           //!< AIMD additive increase parameter
    double m_beta;            //!< AIMD multiplicative decrease factor
    double m_defaultBackoff;  //!< default value when throughput ratio less than default
    double m_throughputRatio; //!< ratio of two consequence throughput
    Time m_delta;            //!< Time since last congestion
    Time m_deltaL;           //!< Threshold for switching between standard and new increase
    Time m_lastCon;          //!< Time of the last congestion
    Time m_minRtt;           //!< Minimum RTT in each congestion period
    Time m_maxRtt;           //!< Maximum RTT in each congestion period
    uint32_t m_throughput;   //!< Current throughput since last congestion
    uint32_t m_lastThroughput; //!< Throughput in last congestion period
    uint32_t m_dataSent;      //!< Current amount of data sent since last congestion
    
};

} // namespace ns3

#endif /* TCP_HTCP_MODIFIED_H */
