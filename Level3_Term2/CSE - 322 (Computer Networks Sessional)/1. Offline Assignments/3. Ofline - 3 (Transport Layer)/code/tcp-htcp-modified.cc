#include "tcp-htcp-modified.h"
#include "ns3/log.h"
#include "ns3/simulator.h"

namespace ns3
{

NS_LOG_COMPONENT_DEFINE("TcpHtcpModified");
NS_OBJECT_ENSURE_REGISTERED(TcpHtcpModified);

TypeId
TcpHtcpModified::GetTypeId()
{
    static TypeId tid = TypeId("ns3::TcpHtcpModified")
        .SetParent<TcpNewReno>()
        .AddConstructor<TcpHtcpModified>()
        .SetGroupName("Internet")
        .AddAttribute("DefaultBackoff",
                      "The default AIMD backoff factor",
                      DoubleValue(0.5),
                      MakeDoubleAccessor(&TcpHtcpModified::m_defaultBackoff),
                      MakeDoubleChecker<double>(0, 1))
        .AddAttribute("ThroughputRatio",
                      "Threshold value for updating beta",
                      DoubleValue(0.2),
                      MakeDoubleAccessor(&TcpHtcpModified::m_throughputRatio),
                      MakeDoubleChecker<double>())
        .AddAttribute("DeltaL",
                      "Delta_L parameter in increase function",
                      TimeValue(Seconds(1)),
                      MakeTimeAccessor(&TcpHtcpModified::m_deltaL),
                      MakeTimeChecker());
    return tid;
}

TcpHtcpModified::TcpHtcpModified()
    : TcpNewReno(),
      m_alpha(0),
      m_beta(0),
      m_delta(0),
      m_lastCon(0),
      m_minRtt(Time::Max()),
      m_maxRtt(Time::Min()),
      m_throughput(0),
      m_lastThroughput(0),
      m_dataSent(0)
{
    NS_LOG_FUNCTION(this);
}

TcpHtcpModified::TcpHtcpModified(const TcpHtcpModified& sock)
    : TcpNewReno(sock),
      m_alpha(sock.m_alpha),
      m_beta(sock.m_beta),
      m_defaultBackoff(sock.m_defaultBackoff),
      m_throughputRatio(sock.m_throughputRatio),
      m_delta(sock.m_delta),
      m_deltaL(sock.m_deltaL),
      m_lastCon(sock.m_lastCon),
      m_minRtt(sock.m_minRtt),
      m_maxRtt(sock.m_maxRtt),
      m_throughput(sock.m_throughput),
      m_lastThroughput(sock.m_lastThroughput),
      m_dataSent(sock.m_dataSent)
{
    NS_LOG_FUNCTION(this);
}

TcpHtcpModified::~TcpHtcpModified()
{
    NS_LOG_FUNCTION(this);
}

/*

void TcpHtcpModified::CongestionAvoidance(Ptr<TcpSocketState> tcb, uint32_t segmentsAcked)
{
    NS_LOG_FUNCTION(this << tcb << segmentsAcked);
    if (segmentsAcked > 0)
    {
        double adder = (m_alpha * tcb->m_segmentSize) / tcb->m_cWnd;
        adder = std::max(1.0, adder);
        tcb->m_cWnd += static_cast<uint32_t>(adder);
        NS_LOG_INFO("In CongAvoid, updated cwnd to " << tcb->m_cWnd);
    }
}


void TcpHtcpModified::UpdateAlpha()
{
    NS_LOG_FUNCTION(this);

    m_delta = Simulator::Now() - m_lastCon;
    if (m_delta <= m_deltaL)
    {
        m_alpha = 1.0;
    }
    else
    {
        Time diff = m_delta - m_deltaL;
        double diffSec = diff.GetSeconds();
        // New alpha calculation according to the paper
        m_alpha = 1 + 0.6 * pow(diffSec, 0.8);
    }
    m_alpha = std::max(1.0, m_alpha);
    NS_LOG_DEBUG("Updated m_alpha: " << m_alpha);
}

void
TcpHtcpModified::UpdateBeta()
{
    NS_LOG_FUNCTION(this);

    // Default value for m_beta
    m_beta = m_defaultBackoff;

    if (m_throughput > m_lastThroughput && m_lastThroughput > 0)
    {
        uint32_t diff = m_throughput - m_lastThroughput;
        if (diff / m_lastThroughput <= m_throughputRatio)
        {
            m_beta = m_minRtt.GetDouble() / m_maxRtt.GetDouble();
        }
    }
    NS_LOG_DEBUG("Updated m_beta: " << m_beta);
}
*/

void TcpHtcpModified::CongestionAvoidance(Ptr<TcpSocketState> tcb, uint32_t segmentsAcked)
{
    NS_LOG_FUNCTION(this << tcb << segmentsAcked);
    if (segmentsAcked > 0)
    {
        // Less aggressive window growth using square root of alpha
        double adder = (sqrt(m_alpha) * tcb->m_segmentSize * tcb->m_segmentSize) / tcb->m_cWnd;
        adder = std::max(2.0, adder); // Minimum increase of 2 segments
        tcb->m_cWnd += static_cast<uint32_t>(adder);
        NS_LOG_INFO("In CongAvoid, updated cwnd to " << tcb->m_cWnd);
    }
}

void TcpHtcpModified::UpdateAlpha()
{
    NS_LOG_FUNCTION(this);

    m_delta = Simulator::Now() - m_lastCon;
    if (m_delta <= m_deltaL)
    {
        m_alpha = 2.0; // More aggressive initial alpha
    }
    else
    {
        Time diff = m_delta - m_deltaL;
        double diffSec = diff.GetSeconds();
        // Steeper increase using cubic function
        m_alpha = 2.0 + 15 * pow(diffSec, 1.5);
    }
    m_alpha = std::max(2.0, m_alpha);
    NS_LOG_DEBUG("Updated m_alpha: " << m_alpha);
}

void TcpHtcpModified::UpdateBeta()
{
    NS_LOG_FUNCTION(this);

    double rttRatio = m_minRtt.GetDouble() / m_maxRtt.GetDouble();

    // Dynamic beta based on RTT ratio
    if (rttRatio > 0.8)
    {
        m_beta = 0.8; // Less reduction in good conditions
    }
    else if (rttRatio > 0.6)
    {
        m_beta = 0.7;
    }
    else
    {
        m_beta = 0.5; // More reduction in poor conditions
    }

    NS_LOG_DEBUG("Updated m_beta: " << m_beta);
}


std::string
TcpHtcpModified::GetName() const
{
    return "TcpHtcpModified";
}

Ptr<TcpCongestionOps>
TcpHtcpModified::Fork()
{
    return CopyObject<TcpHtcpModified>(this);
}

uint32_t
TcpHtcpModified::GetSsThresh(Ptr<const TcpSocketState> tcb, uint32_t bytesInFlight)
{
    NS_LOG_FUNCTION(this << tcb << bytesInFlight);
    m_lastCon = Simulator::Now();
    UpdateBeta();
    UpdateAlpha();
    uint32_t segWin = 2 * tcb->m_segmentSize;
    auto bFlight = static_cast<uint32_t>(bytesInFlight * m_beta);
    uint32_t ssThresh = std::max(segWin, bFlight);
    m_minRtt = Time::Max();
    m_maxRtt = Time::Min();
    m_lastThroughput = m_throughput;
    m_throughput = 0;
    m_dataSent = 0;
    return ssThresh;
}

void
TcpHtcpModified::PktsAcked(Ptr<TcpSocketState> tcb, uint32_t segmentsAcked, const Time& rtt)
{
    NS_LOG_FUNCTION(this << tcb << segmentsAcked << rtt);
    if (tcb->m_congState == TcpSocketState::CA_OPEN)
    {
        m_dataSent += segmentsAcked * tcb->m_segmentSize;
    }
    m_throughput = static_cast<uint32_t>(m_dataSent /
                                       (Simulator::Now().GetSeconds() - m_lastCon.GetSeconds()));
    UpdateAlpha();
    if (rtt < m_minRtt)
    {
        m_minRtt = rtt;
    }
    if (rtt > m_maxRtt)
    {
        m_maxRtt = rtt;
    }
}

} // namespace ns3
