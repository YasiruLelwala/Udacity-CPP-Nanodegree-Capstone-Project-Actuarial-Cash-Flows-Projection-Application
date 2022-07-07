#ifndef PORTFOLIO_CASH_FLOWS
#define PORTFOLIO_CASH_FLOWS

#include <mutex>
#include <condition_variable>

#include "Policy.h"
#include "TimeStepProjection.h"
#include "DecrementsProjection.h"
#include "CashFlowsProjection.h"
#include "CashFlowsProjectionByValuationYear.h"

class PortfolioCashFlows
{
public:
    // constructor
    PortfolioCashFlows() {};

    ~PortfolioCashFlows() { std::cout << "PortfoliosCashFlows object destructed" << std::endl; };

    // getters
    std::vector<std::shared_ptr<Policy>> &getPolicyVector() { return _policyVector; };
    std::vector<std::shared_ptr<TimeStepProjection>> &getTimeStepProjectionVector() { return _timeStepProjectionVector; };
    std::vector<std::shared_ptr<DecrementsProjection>> &getDecrementsProjectionVector() { return _decrementsProjectionVector; };
    std::vector<std::shared_ptr<CashFlowsProjection>> &getCashFlowsProjectionVector() { return _cashFlowsProjectionVector; };
    std::vector<std::shared_ptr<CashFlowsProjectionByValuationYear>> &getCashFlowsProjectionByValuationYearVector() { return _cashFlowsProjectionByValuationYearVector; };
    
    std::map<int,std::vector<double>> &getPortfolioCashFlowsByValuationYear() {return _portfolioCashFlowsByValuationYear; };

    // print methods
    void printPortfolioCashFlows();

    // methods
    void run();


    void pushBackPolicy(std::shared_ptr<Policy> policy);
    void pushBackTimeStepProjection(std::shared_ptr<TimeStepProjection> timeStepProjection);
    void pushBackDecrementsProjection(std::shared_ptr<DecrementsProjection> decrementsProjection);
    void pushBackCashFlowsProjection (std::shared_ptr<CashFlowsProjection> cashFlowsProjection);
    void pushBackCashFlowsProjectionByValuationYear (std::shared_ptr<CashFlowsProjectionByValuationYear> cashFlowsProjectionByValuationYear);

    std::map<int,std::vector<double>> createPortfolioCashFlowsByValuationYear();

    //Policy popBack();
    

private:
    std::mutex _mutex;
    
    std::vector<std::shared_ptr<Policy>> _policyVector;
    std::vector<std::shared_ptr<TimeStepProjection>> _timeStepProjectionVector;
    std::vector<std::shared_ptr<DecrementsProjection>> _decrementsProjectionVector;
    std::vector<std::shared_ptr<CashFlowsProjection>> _cashFlowsProjectionVector;
    std::vector<std::shared_ptr<CashFlowsProjectionByValuationYear>> _cashFlowsProjectionByValuationYearVector;

    std::map<int,std::vector<double>> _portfolioCashFlowsByValuationYear;

    
};

#endif