#include "PortfolioCashFlows.h"

void PortfolioCashFlows::printPortfolioCashFlows()
{
    std::ofstream myFile("../results/portfolioCashFlowsByValuationYear.csv");

    myFile 
    << "VALUATION_YEAR" << "," 
    << "EXPECTED_PREMIUM" << ","
    << "EXPECTED_DEATH_OUTGO" << std::endl;
    
    const std::map<int,std::vector<double>> &portfolioCashFlowsByValuationYear = this->getPortfolioCashFlowsByValuationYear();

    for (auto i = portfolioCashFlowsByValuationYear.begin(); i != portfolioCashFlowsByValuationYear.end(); i++)
    {
        myFile << i->first << "," 
        << i->second[0] <<  "," 
        << i->second[1] << std::endl;
        

    }
    myFile.close();
}


void PortfolioCashFlows::run()
{
    this->_portfolioCashFlowsByValuationYear = PortfolioCashFlows::createPortfolioCashFlowsByValuationYear();
    
    PortfolioCashFlows::printPortfolioCashFlows();
}

void PortfolioCashFlows::pushBackPolicy(Policy &&policy) 
{
    // simulate some work
    //std::this_thread::sleep_for(std::chrono::milliseconds(100));

    // perform vector modification under the lock
    std::lock_guard<std::mutex> uLock(_mutex);

    // add vector to queue
    //std::cout << "Policy #" << policy.getID() << " will be added to the queue" << std::endl;
    _policyVector.push_back(std::move(policy));
    //_cond.notify_one(); // notify client after pushing new Object A into vector
};

void PortfolioCashFlows::pushBackTimeStepProjection(TimeStepProjection &&timeStepProjection)
{
    // simulate some work
    //std::this_thread::sleep_for(std::chrono::milliseconds(100));

    // perform vector modification under the lock
    std::lock_guard<std::mutex> uLock(_mutex);

    // add vector to queue
    //std::cout << "TimeStep Projection #" << timeStepProjection.getPolicy().getID() << " will be added to the queue" << std::endl;
    _timeStepProjectionVector.push_back(std::move(timeStepProjection));
    //_cond.notify_one(); // notify client after pushing new Object A into vector
}

void PortfolioCashFlows::pushBackDecrementsProjection(DecrementsProjection &&decrementsProjection)
{
    // simulate some work
    //std::this_thread::sleep_for(std::chrono::milliseconds(100));

    // perform vector modification under the lock
    std::lock_guard<std::mutex> uLock(_mutex);

    // add vector to queue
    //std::cout << "Decrements Projection #" << decrementsProjection.getTimeStepProjection().getPolicy().getID() << " will be added to the queue" << std::endl;
    _decrementsProjectionVector.push_back(std::move(decrementsProjection));
    //_cond.notify_one(); // notify client after pushing new Object A into vector
}

void PortfolioCashFlows::pushBackCashFlowsProjection (CashFlowsProjection &&cashFlowsProjection)
{
    // simulate some work
    //std::this_thread::sleep_for(std::chrono::milliseconds(100));

    // perform vector modification under the lock
    std::lock_guard<std::mutex> uLock(_mutex);

    // add vector to queue
    //std::cout << "CashFlows Projection #" << cashFlowsProjection.getDecrementsProjection().getTimeStepProjection().getPolicy().getID() << " will be added to the queue" << std::endl;
    _cashFlowsProjectionVector.push_back(std::move(cashFlowsProjection));
}

void PortfolioCashFlows::pushBackCashFlowsProjectionByValuationYear (CashFlowsProjectionByValuationYear &&cashFlowsProjectionByValuationYear)
{
    // simulate some work
    //std::this_thread::sleep_for(std::chrono::milliseconds(100));

    // perform vector modification under the lock
    std::lock_guard<std::mutex> uLock(_mutex);

    // add vector to queue
    //std::cout << "CashFlows Projection By Valuation Year #" << cashFlowsProjectionByValuationYear.getCashFlowsProjection().getDecrementsProjection().getTimeStepProjection().getPolicy().getID() << " will be added to the queue" << std::endl;
    _cashFlowsProjectionByValuationYearVector.push_back(std::move(cashFlowsProjectionByValuationYear));
}

std::map<int,std::vector<double>> PortfolioCashFlows::createPortfolioCashFlowsByValuationYear()
{
     auto your_sum = [](const std::vector<double> &cont1, const std::vector<double> &cont2)
    {
        std::vector<double> result;
        //const auto smaller = std::min(cont1.size(), cont2.size());
        for ( size_t i = 0 ; i < cont1.size(); i++)
        {
              result.push_back(cont1[i]+cont2[i]);  
        }
        return result;
    };


    std::map<int,std::vector<double>> portfolioCashFlowsByValuationYear;

    for (int i = 0; i < _cashFlowsProjectionByValuationYearVector.size(); i++)
    {
        std::for_each(_cashFlowsProjectionByValuationYearVector[i].getCashFlowsByValuationYear().begin(), _cashFlowsProjectionByValuationYearVector[i].getCashFlowsByValuationYear().end(), [&portfolioCashFlowsByValuationYear, &your_sum] (auto &j) {

            if ( portfolioCashFlowsByValuationYear.count(j.first) > 0)
            {
                portfolioCashFlowsByValuationYear.at(j.first) = your_sum(j.second, portfolioCashFlowsByValuationYear.at(j.first));
            }
            else
            {
                portfolioCashFlowsByValuationYear.insert({j.first, j.second});
            }

        });
    }

    return portfolioCashFlowsByValuationYear;

}

