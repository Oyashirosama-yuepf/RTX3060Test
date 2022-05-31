#ifndef  HOLO_C_COMMON_USS_DDS_APA01_H_
#define HOLO_C_COMMON_USS_DDS_APA01_H_
#include <holo/common/timestamp.h>
#include <holo/core/types.h>
#include <holo/serialization/serialization.h>

namespace holo
{
namespace common
{
namespace details
{
/////////////////////////DDSUSSApa01///////////////////////////////////////////
class  DDSUSSApa01
{
public:
    DDSUSSApa01()
    {
        this->dds_AbsltPinionAgReq = 0;
        this->dds_AbsltPinionAgReqValid = 0;
        this->dds_APA_EPSReqTyp = 0;//this string have _ , do not move
        this->dds_ApaAbortReason = 0;
        this->dds_ApaInstruction = 0;
        this->dds_ApaManeuverDst = 0;
        this->dds_ApaMaxVelocity = 0;
        this->dds_ApaOperatingMode = 0;
        this->dds_APASts = 0;
        this->dds_FrntLeMidRegnDst = 0;
        this->dds_FrntLeRegnDst = 0;
        this->dds_FrntMidRegnDst = 0;
        this->dds_FrntRiMidRegnDst = 0;
        this->dds_FrntRiRegnDst = 0;
        this->dds_FrntSnsrDegSt = 0;
        this->dds_FrntSysSts = 0;
        this->dds_ReLeMidRegnDst = 0;
        this->dds_ReLeRegnDst = 0;
        this->dds_ReMidRegnDst = 0;
        this->dds_ReRiMidRegnDst = 0;
        this->dds_ReRiRegnDst = 0;
        this->dds_ReSnsrDegSt = 0;
        this->dds_ReSysSts = 0;
        this->dds_UpaSysDi = 0;
        this->dds_UpaSysSrv = 0;
        this->dds_UpaSysSts = 0;
        this->dds_VmmSPos = 0;
        this->dds_VmmXPos = 0;
        this->dds_mmYawAngle = 0;
        this->dds_VmmYPos = 0;
    }
    ~DDSUSSApa01()
    {
        this->dds_AbsltPinionAgReq = 0;
        this->dds_AbsltPinionAgReqValid = 0;
        this->dds_APA_EPSReqTyp = 0;//this string have _ , do not move
        this->dds_ApaAbortReason = 0;
        this->dds_ApaInstruction = 0;
        this->dds_ApaManeuverDst = 0;
        this->dds_ApaMaxVelocity = 0;
        this->dds_ApaOperatingMode = 0;
        this->dds_APASts = 0;
        this->dds_FrntLeMidRegnDst = 0;
        this->dds_FrntLeRegnDst = 0;
        this->dds_FrntMidRegnDst = 0;
        this-> dds_FrntRiMidRegnDst = 0;
        this->dds_FrntRiRegnDst = 0;
        this->dds_FrntSnsrDegSt = 0;
        this->dds_FrntSysSts = 0;
        this->dds_ReLeMidRegnDst = 0;
        this->dds_ReLeRegnDst = 0;
        this-> dds_ReMidRegnDst = 0;
        this->dds_ReRiMidRegnDst = 0;
        this->dds_ReRiRegnDst = 0;
        this->dds_ReSnsrDegSt = 0;
        this->dds_ReSysSts = 0;
        this->dds_UpaSysDi = 0;
        this->dds_UpaSysSrv = 0;
        this->dds_UpaSysSts = 0;
        this->dds_VmmSPos = 0;
        this->dds_VmmXPos = 0;
        this->dds_mmYawAngle = 0;
        this->dds_VmmYPos = 0;
    }
    ///////////////////////////////////////DDSUSSApa01 get//////////////////////////////////////////////////////////////////////////////
    holo::float32_t  Ussapa01GetDdsAbsltpinionagreq()
    {     
        if(NULL== this)
        {
            return  0;
        }
        return this->dds_AbsltPinionAgReq;
    }
    holo::uint8_t  Ussapa01GetDdsAbsltpinionagreqvalid()
    {    
        if(NULL== this)
        {
            return  0;
        }
        return this->dds_AbsltPinionAgReqValid;
    }
    holo::uint8_t  Ussapa01GetDdsApa_epsreqtyp()
    {   
        if(NULL== this)
        {
            return  0;
        }
        return this->dds_APA_EPSReqTyp;//this string have _ , do not move
    }
    holo::uint8_t  Ussapa01GetDdsApaabortreason()
    {  
        if(NULL== this)
        {
            return  0;
        }
        return this->dds_ApaAbortReason;
    }
    holo::uint8_t  ussapa01GetApaInstruction()
    {    
        if(NULL== this)
        {
            return  0;
        }
        return this->dds_ApaInstruction;
    }
    holo::uint16_t    Ussapa01GetDdsApamaneuverdst()
    {    
        if(NULL== this)
        {
            return  0;
        }
        return this->dds_ApaManeuverDst;
    }
    holo::float32_t  Ussapa01GetDdsApamaxvelocity()
    {
        if(NULL== this)
        {
            return  0;
        }
        return this->dds_ApaOperatingMode;
    }
    holo::uint8_t     Ussapa01GetDdsApasts()
    {   
        if(NULL== this)
        {
            return  0;
        }
        return this->dds_APASts;
    }
    holo::uint8_t     Ussapa01GetDdsFrntlemidregndst()
    {   
        if(NULL== this)
        {
            return  0;
        }
        return this->dds_FrntLeMidRegnDst;
    }
    holo::uint8_t     Ussapa01GetDdsFrntleregndst()
    {   
        if(NULL== this)
        {
            return  0;
        }
        return this->dds_FrntLeRegnDst;
    }
    holo::uint8_t      Ussapa01GetDdsFrntmidregndst()
    {   
        if(NULL== this)
        {
            return  0;
        }
        return this->dds_FrntMidRegnDst;
    }
    holo::uint8_t     Ussapa01GetDdsFrntrimidregndst()
    {    
        if(NULL== this)
        {
            return  0;
        }
        return this->dds_FrntRiMidRegnDst;
    }
    holo::uint8_t     Ussapa01GetDdsFrntriregndst()
    {   
        if(NULL== this)
        {
            return  0;
        }
        return this->dds_FrntRiRegnDst;
    }
    holo::uint8_t     Ussapa01GetDdsFrntsnsrdegst()
    {    
        if(NULL== this)
        {
            return  0;
        }
        return this->dds_FrntSnsrDegSt;
    }
    holo::uint8_t    Ussapa01GetDdsFrntsyssts()
    {    
        if(NULL== this)
        {
            return  0;
        }
        return this->dds_FrntSysSts;
    }
    holo::uint8_t     Ussapa01GetDdsRelemidregndst()
    {    
        if(NULL== this)
        {
            return  0;
        }
        return this->dds_ReLeMidRegnDst;
    }
    holo::uint8_t    Ussapa01GetDdsReleregndst()
    {   
        if(NULL== this)
        {
            return  0;
        }
        return this->dds_ReLeRegnDst;
    }
    holo::uint8_t    Ussapa01GetDdsRemidregndst()
    {    
        if(NULL== this)
        {
            return  0;
        }
        return this->dds_ReMidRegnDst;
    }
    holo::uint8_t    Ussapa01GetDdsRerimidregndst()
    {  
        if(NULL== this)
        {
            return  0;
        }
        return this->dds_ReMidRegnDst;
    }
    holo::uint8_t     Ussapa01GetDdsReriregndst()
    {     
        if(NULL== this)
        {
            return  0;
        }
        return this->dds_ReRiRegnDst;
    }
    holo::uint8_t     Ussapa01GetDdsResnsrdegst()
    {    
        if(NULL== this)
        {
            return  0;
        }
        return this->dds_ReSnsrDegSt;
    }
    holo::uint8_t     Ussapa01GetDdsResyssts()
    {     
        if(NULL== this)
        {
            return  0;
        }
        return this->dds_ReSysSts;
    }
    holo::uint8_t     Ussapa01GetDdsUpasysdi()
    {     
        if(NULL== this)
        {
            return  0;
        }
        return this->dds_UpaSysDi;
    }
    holo::uint8_t     Ussapa01GetDdsUpasyssrv()
    {     
        if(NULL== this)
        {
            return  0;
        }
        return this->dds_UpaSysSrv;
    }
    holo::uint8_t     Ussapa01GetDdsUpasyssts()
    {    
        if(NULL== this)
        {
            return  0;
        }
        return this->dds_UpaSysSts;
    }
    holo::int32_t     Ussapa01GetDdsVmmspos()
    {    
        if(NULL== this)
        {
            return  0;
        }
        return this->dds_VmmSPos;
    }
    holo::int32_t     Ussapa01GetDdsVmmxpos()
    {    
        if(NULL== this)
        {
            return  0;
        }
        return this->dds_VmmXPos;
    }
    holo::uint8_t     Ussapa01GetDdsmmYawAngle()
    {     
        if(NULL== this)
        {
            return  0;
        }
        return this->dds_mmYawAngle;
    }
    holo::int32_t      Ussapa01GetDdsVmmypos()
    {     
        if(NULL== this)
        {
            return 0;
        }
        return this->dds_VmmYPos;
    }
    Timestamp GetTimestamp() const noexcept
    {
        return timestamp_;
    }

    //////////////////////////DDSUSSApa01 set/////////////////////////////////////////////////////////////////////////////
    void  Ussapa01SetDdsAbsltpinionagreq( const  holo::float32_t value)
    {
        if(NULL== this)
        {
            return;
        }
        this->dds_AbsltPinionAgReq  =  value;
    }
    void Ussapa01SetDdsAbsltpinionagreqvalid( const holo::uint8_t  value)
    {
        if(NULL== this)
        {
            return;
        }
        this->dds_AbsltPinionAgReqValid  =  value;
    }
    void Ussapa01SetDdsApa_epsreqtyp( const holo::uint8_t value)
    {
        if(NULL== this)
        {
            return;
        }
        this->dds_APA_EPSReqTyp  =  value;//this string have _ , do not move
    }
    void  Ussapa01SetDdsApaabortreason( const  holo::uint8_t value)
    {
        if(NULL== this)
        {
            return;
        }
        this->dds_ApaAbortReason  =  value;
    }
    void Ussapa01SetDdsApainstruction( const  holo::uint8_t value)
    {
        if(NULL== this)
        {
            return;
        }
        this->dds_ApaInstruction  =  value;
    }
    void  Ussapa01SetDdsApamaneuverdst( const holo::uint16_t  value)
    {
        if(NULL== this)
        {
            return;
        }
        this->dds_ApaManeuverDst  =  value;
    }
    void Ussapa01SetDdsApamaxvelocity( const holo::float32_t  value)
    {
        if(NULL== this)
        {
            return;
        }
        this->dds_ApaMaxVelocity  =  value;
    }
    void Ussapa01SetDdsApaoperatingmode( const  holo::uint8_t value)
    {
        if(NULL== this)
        {
            return;
        }
        this->dds_ApaOperatingMode  =  value;
    }
    void    Ussapa01SetDdsApasts( const  holo::uint8_t value)
    {
        if(NULL== this)
        {
            return;
        }
        this->dds_APASts  =  value;
    }
    void     Ussapa01SetDdsFrntlemidregndst( const holo::uint8_t  value)
    {
        if(NULL== this)
        {
            return;
        }
        this->dds_FrntLeMidRegnDst  =  value;
    }
    void     Ussapa01SetDdsFrntleregndst( const  holo::uint8_t value)
    {
        if(NULL== this)
        {
            return;
        }
        this->dds_FrntLeRegnDst  =  value;
    }
    void      Ussapa01SetDdsFrntmidregndst( const holo::uint8_t  value)
    {
        if(NULL== this)
        {
            return;
        }
        this->dds_FrntMidRegnDst  =  value;
    }
    void     Ussapa01SetDdsFrntrimidregndst( const  holo::uint8_t value)
    {
        if(NULL== this)
        {
            return;
        }
        this->dds_FrntRiMidRegnDst  =  value;
    }
    void     Ussapa01SetDdsFrntriregndst( const  holo::uint8_t value)
    {
        if(NULL== this)
        {
            return;
        }
        this->dds_FrntRiRegnDst  =  value;
    }
    void     Ussapa01SetDdsFrntsnsrdegst( const  holo::uint8_t value)
    {
        if(NULL== this)
        {
            return;
        }
        this->dds_FrntSnsrDegSt  =  value;
    }
    void    Ussapa01SetDdsFrntsyssts( const holo::uint8_t  value)
    {
        if(NULL== this)
        {
            return;
        }
        this->dds_FrntSysSts  =  value;
    }
    void    Ussapa01SetDdsRelemidregndst( const  holo::uint8_t value)
    {
        if(NULL== this)
        {
            return;
        }
        this->dds_ReLeMidRegnDst  =  value;
    }
    void    Ussapa01SetDdsReleregndst( const  holo::uint8_t value)
    {
        if(NULL== this)
        {
            return;
        }
        this->dds_ReLeRegnDst  =  value;
    }
    void    Ussapa01SetDdsRemidregndst( const holo::uint8_t  value)
    {
        if(NULL== this)
        {
            return;
        }
        this->dds_ReMidRegnDst  =  value;
    }
    void Ussapa01SetDdsRerimidregndst( const  holo::uint8_t value)
    {
            if(NULL== this)
        {
            return;
        }
        this->dds_ReMidRegnDst  =  value;
    }
    void Ussapa01SetDdsReriregndst( const  holo::uint8_t value)
    {
        if(NULL== this)
        {
            return;
        }
        this->dds_ReRiRegnDst  =  value;
    }
    void Ussapa01SetDdsResnsrdegst( const  holo::uint8_t value)
    {
        if(NULL== this)
        {
            return;
        }
        this->dds_ReSnsrDegSt  =  value;
    }
    void Ussapa01SetDdsResyssts( const  holo::uint8_t value)
    {
        if(NULL== this)
        {
            return;
        }
        this->dds_ReSysSts  =  value;
    }
    void  Ussapa01SetDdsUpasysdi( const  holo::uint8_t value)
    {
        if(NULL== this)
        {
            return;
        }
        this->dds_UpaSysDi  =  value;
    }
    void  Ussapa01SetDdsUpasyssrv( const  holo::uint8_t value)
    {
        if(NULL== this)
        {
            return;
        }
        this->dds_UpaSysSrv  =  value;
    }
    void    Ussapa01SetDdsUpasyssts( const  holo::uint8_t  value)
    {
        if(NULL== this)
        {
            return;
        }
        this->dds_UpaSysSts  =  value;
    }
    void     Ussapa01SetDdsVmmspos( const  holo::int32_t value)
    {
        if(NULL== this)
        {
            return;
        }
        this->dds_VmmSPos  =  value;
    }
    //fmh add start 20220223 
    void     Ussapa01SetDdsVmmxpos( const holo::int32_t  value)
    {
        if(NULL== this)
        {
            return;
        }
        this->dds_VmmXPos  =  value;
    }
     void     Ussapa01SetDdsVmmypos( const holo::int32_t  value)
    {
        if(NULL== this)
        {
            return;
        }
        this->dds_VmmYPos  =  value;
    }
    void   Ussapa01SetDdsmmYawAngle(const holo::uint8_t  value)
    {     
        if(NULL== this)
        {
            return;
        }
         this->dds_mmYawAngle = value;
    }
    //fmh add end 20220223 
    void SetTimestamp(Timestamp const timestamp)
    {
        this->timestamp_ = timestamp;
    }
    //////////////////////////////////////
    template <size_t ALIGN = 4U>
    size_t GetSerializedSize() const noexcept
    {
        return timestamp_.GetSerializedSize<ALIGN>() +
               holo::serialization::SerializedSize<ALIGN>(
        this->dds_AbsltPinionAgReq ,  this->dds_AbsltPinionAgReqValid ,  this->dds_APA_EPSReqTyp ,
        this->dds_ApaAbortReason ,  this->dds_ApaInstruction ,  this->dds_ApaManeuverDst ,  this->dds_ApaMaxVelocity ,
        this->dds_ApaOperatingMode ,  this->dds_APASts ,  this->dds_FrntLeMidRegnDst , this-> dds_FrntLeRegnDst ,
        this->dds_FrntMidRegnDst ,  this->dds_FrntRiMidRegnDst ,  this->dds_FrntRiRegnDst , this->dds_FrntSnsrDegSt ,  
		this->dds_FrntSysSts ,this->dds_ReLeMidRegnDst ,  this->dds_ReLeRegnDst ,  this->dds_ReMidRegnDst , 
		this->dds_ReRiMidRegnDst,  this->dds_ReRiRegnDst, this->dds_ReSnsrDegSt, this->dds_ReSysSts, 
		this->dds_UpaSysDi, this->dds_UpaSysSrv, 
		this->dds_UpaSysSts, this->dds_VmmSPos,this->dds_VmmXPos, this->dds_mmYawAngle, this->dds_VmmYPos);
	}

    template <typename S>
    void Serialize(S& serializer) const
    {
        serializer <<  this->timestamp_ 
        <<  this->dds_AbsltPinionAgReq <<  this->dds_AbsltPinionAgReqValid <<this->dds_APA_EPSReqTyp
         <<this->dds_ApaAbortReason <<   this->dds_ApaInstruction <<  this->dds_ApaManeuverDst << this->dds_ApaMaxVelocity 
         << this->dds_ApaOperatingMode <<  this->dds_APASts <<  this->dds_FrntLeMidRegnDst <<  this->dds_FrntLeRegnDst
         <<this->dds_FrntMidRegnDst <<  this->dds_FrntRiMidRegnDst <<  this->dds_FrntRiRegnDst <<  this->dds_FrntSnsrDegSt
        << this->dds_FrntSysSts <<this->dds_ReLeMidRegnDst <<  this->dds_ReLeRegnDst <<  this->dds_ReMidRegnDst 
        << this->dds_ReRiMidRegnDst<< this->dds_ReRiRegnDst<< this->dds_ReSnsrDegSt<< this->dds_ReSysSts
        << this->dds_UpaSysDi<< this->dds_UpaSysSrv
        <<  this->dds_UpaSysSts<< this->dds_VmmSPos<< this->dds_VmmXPos<< this->dds_mmYawAngle<< this->dds_VmmYPos
        <<holo::serialization::align;
    }

    template <typename D>
    void Deserialize(D& deserializer)
    {
        deserializer >>  this->timestamp_ 
        >>  this->dds_AbsltPinionAgReq >>  this->dds_AbsltPinionAgReqValid  >>  this->dds_APA_EPSReqTyp 
        >>this->dds_ApaAbortReason >>  this->dds_ApaInstruction >>  this->dds_ApaManeuverDst >>  this->dds_ApaMaxVelocity
        >>this->dds_ApaOperatingMode >>  this->dds_APASts >>  this->dds_FrntLeMidRegnDst >> this->dds_FrntLeRegnDst
        >> this->dds_FrntMidRegnDst >>  this->dds_FrntRiMidRegnDst>> this->dds_FrntRiRegnDst >>   this->dds_FrntSnsrDegSt 
        >>  this->dds_FrntSysSts >>this->dds_ReLeMidRegnDst >>  this->dds_ReLeRegnDst >>  this->dds_ReMidRegnDst
         >> this->dds_ReRiMidRegnDst>>  this->dds_ReRiRegnDst>> this->dds_ReSnsrDegSt>>dds_ReSysSts
        >>this->dds_UpaSysDi>> this->dds_UpaSysSrv
        >> this->dds_UpaSysSts>> this->dds_VmmSPos>> this->dds_VmmXPos>>this->dds_mmYawAngle>> this->dds_VmmYPos
        >>holo::serialization::align;
    }
private:
    //APA_01
    holo::float32_t  dds_AbsltPinionAgReq;
    holo::uint8_t      dds_AbsltPinionAgReqValid;
    holo::uint8_t       dds_APA_EPSReqTyp;//this string have _ , do not move
    holo::uint8_t       dds_ApaAbortReason;
    holo::uint8_t      dds_ApaInstruction;
    holo::uint16_t    dds_ApaManeuverDst;
    holo::float32_t  dds_ApaMaxVelocity;
    holo::uint8_t     dds_ApaOperatingMode;
    holo::uint8_t     dds_APASts;
    holo::uint8_t     dds_FrntLeMidRegnDst;
    holo::uint8_t     dds_FrntLeRegnDst;
    holo::uint8_t      dds_FrntMidRegnDst;
    holo::uint8_t     dds_FrntRiMidRegnDst;
    holo::uint8_t     dds_FrntRiRegnDst;
    holo::uint8_t     dds_FrntSnsrDegSt;
    holo::uint8_t    dds_FrntSysSts;
    holo::uint8_t    dds_ReLeMidRegnDst;
    holo::uint8_t    dds_ReLeRegnDst;
    holo::uint8_t    dds_ReMidRegnDst;
    holo::uint8_t    dds_ReRiMidRegnDst;
    holo::uint8_t     dds_ReRiRegnDst;
    holo::uint8_t     dds_ReSnsrDegSt;
    holo::uint8_t     dds_ReSysSts;
    holo::uint8_t     dds_UpaSysDi;
    holo::uint8_t     dds_UpaSysSrv;
    holo::uint8_t     dds_UpaSysSts;
    holo::int32_t     dds_VmmSPos;
    holo::int32_t     dds_VmmXPos;
    holo::uint8_t     dds_mmYawAngle;
    holo::int32_t      dds_VmmYPos;

    holo::common::Timestamp timestamp_;  ///< Timestamp of this object.
};// DDSUSSApa01

}  // namespace details
}  // namespace common
}  // namespace holo
#endif//HOLO_C_COMMON_USS_DDS_APA01_H_