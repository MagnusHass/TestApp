// Include files
#include "Backup.hpp"
#include "MessageId.h"
#include "SafetyCatchHandler.hpp"
#include "ParameterAdapter.hpp"
#include "ParameterDMC.hpp"
#include "SystemConfiguration.hpp"
#include "OptionHandler.hpp"

// Explicit instantiation
template class Array < INT32, ( UINT16 )( SysDefs::VERY_HIGH + 1 ) >;

/*****************************************************************************/
/**
 * \brief   Construc tor
 *
 *****************************************************************************/
Backup::Backup( const ParameterAdapter &myMaster )
    : ModeDepParObserver( myMaster, TRUE, FALSE, ModeDepParObserver::MODE_ONLY ),
      m_incrementSafetyCatchHandler( MessageId::MSG_HIGH_BACKUP_PRESS,
                                     SafetyCatchHandler::STANDARD_SAFETY_CATCH_TIME_ONE_SEC ), // removed kommas
      m_peepAdapter(),
      m_patientTypeAdapter()
{
    for( UINT16 i = 0; i <= ( UINT16 ) SysDefs::VERY_HIGH; i++ )
    {
        m_regionEndLimit[ i ] = NO_LIMIT;
    }

    m_regionEndLimit[( UINT16 ) SysDefs::NORMAL ] = NORMAL_END_LIMIT;
    m_regionEndLimit[( UINT16 ) SysDefs::HIGH ] = HIGH_END_LIMIT;
    m_regionEndLimit[( UINT16 ) SysDefs::VERY_HIGH ] = VERY_HIGH_END_LIMIT;


    // subscribe on master parameter changes to make sure region is updated corerectly.
    Subject::CombinedSet interestingChanges = ( Parameter::VALUE_CHANGED |
            Parameter::PENDING_VALUE_CHANGED );

    SubscribeInfo *masterInfoPtr =  new SubscribeInfo( interestingChanges,
            masterAdapter.getId() );

    affectionList.append( masterInfoPtr );
    safetyCatchList.append( &m_incrementSafetyCatchHandler );

}