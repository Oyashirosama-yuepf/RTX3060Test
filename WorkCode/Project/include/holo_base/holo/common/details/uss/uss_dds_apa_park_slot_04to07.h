#ifndef  HOLO_C_COMMON_USS_DDS_APA_PARK_SLOT_04TO07_H_
#define HOLO_C_COMMON_USS_DDS_APA_PARK_SLOT_04TO07_H_
#include <holo/common/timestamp.h>
#include <holo/core/types.h>
#include <holo/serialization/serialization.h>
// #ifdef __cplusplus
// extern "C" {
// #endif


namespace holo
{
namespace common
{
namespace details
{
static const unsigned int  SLOT_04TO07_ARRAY_NUMBER = 7;
//////////////////////////////////////////////////////////////////////////////////////
/////////////////////////DDSUSSApaSlot///////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
class DDSUSSApaSlot
{
public:
    ///////////////////////construct////////////////////////////
    DDSUSSApaSlot()
    {
        this->dds_ApaSlotLeID  =0;
        this-> dds_ApaSlotLeObj1Alpha  =0;
        this-> dds_ApaSlotLeObj1X  =0;
        this->dds_ApaSlotLeObj1Y  =0;
        this-> dds_ApaSlotLeObj2Alpha  =0;
        this->dds_ApaSlotLeObj2X  =0;
        this->dds_ApaSlotLeObj2Y  =0;
        this->dds_ApaSlotLeSizeX  =0;
        this->dds_ApaSlotLeSizeY  =0;
        this->dds_ApaSlotLeSts  =0;
        this->dds_ApaSlotLeVehX  =0;
        this->dds_ApaSlotLeVehY  =0;
        this->dds_ApaSlotLeVehPsi  =0;
    }
    ~DDSUSSApaSlot()
    {
        this->dds_ApaSlotLeID  =0;
        this->dds_ApaSlotLeObj1Alpha  =0;
        this->dds_ApaSlotLeObj1X  =0;
        this->dds_ApaSlotLeObj1Y  =0;
        this->dds_ApaSlotLeObj2Alpha  =0;
        this->dds_ApaSlotLeObj2X  =0;
        this->dds_ApaSlotLeObj2Y  =0;
        this->dds_ApaSlotLeSizeX  =0;
        this->dds_ApaSlotLeSizeY  =0;
        this->dds_ApaSlotLeSts  =0;
        this->dds_ApaSlotLeVehX  =0;
        this->dds_ApaSlotLeVehY  =0;
        this->dds_ApaSlotLeVehPsi  =0;
    }
    //DDSUSSApaSlot (const DDSUSSApaSlot & rhs) = delete; 
    //DDSUSSApaSlot & operator=(const DDSUSSApaSlot & rhs) = delete; 
    DDSUSSApaSlot(const DDSUSSApaSlot& t)
     {
        this->dds_ApaSlotLeID  = t.dds_ApaSlotLeID;
        this->dds_ApaSlotLeObj1Alpha  = t.dds_ApaSlotLeObj1Alpha;
        this->dds_ApaSlotLeObj1X  = t.dds_ApaSlotLeObj1X;
        this->dds_ApaSlotLeObj1Y  = t.dds_ApaSlotLeObj1Y;
        this->dds_ApaSlotLeObj2Alpha  = t.dds_ApaSlotLeObj2Alpha;
        this->dds_ApaSlotLeObj2X  = t.dds_ApaSlotLeObj2X;
        this->dds_ApaSlotLeObj2Y  = t.dds_ApaSlotLeObj2Y;
        this->dds_ApaSlotLeSizeX  = t.dds_ApaSlotLeSizeX;
        this->dds_ApaSlotLeSizeY  = t.dds_ApaSlotLeSizeY;
        this->dds_ApaSlotLeSts  = t.dds_ApaSlotLeSts;
        this->dds_ApaSlotLeVehX  = t.dds_ApaSlotLeVehX;
        this->dds_ApaSlotLeVehY  = t.dds_ApaSlotLeVehY;
        this->dds_ApaSlotLeVehPsi  = t.dds_ApaSlotLeVehPsi;
    }
    DDSUSSApaSlot& operator=(const DDSUSSApaSlot& t)
    {
        this->dds_ApaSlotLeID  = t.dds_ApaSlotLeID;
       this-> dds_ApaSlotLeObj1Alpha  = t.dds_ApaSlotLeObj1Alpha;
        this->dds_ApaSlotLeObj1X  = t.dds_ApaSlotLeObj1X;
        this->dds_ApaSlotLeObj1Y  = t.dds_ApaSlotLeObj1Y;
        this->dds_ApaSlotLeObj2Alpha  = t.dds_ApaSlotLeObj2Alpha;
        this->dds_ApaSlotLeObj2X  = t.dds_ApaSlotLeObj2X;
        this->dds_ApaSlotLeObj2Y  = t.dds_ApaSlotLeObj2Y;
        this->dds_ApaSlotLeSizeX  = t.dds_ApaSlotLeSizeX;
        this->dds_ApaSlotLeSizeY  = t.dds_ApaSlotLeSizeY;
        this->dds_ApaSlotLeSts  = t.dds_ApaSlotLeSts;
        this->dds_ApaSlotLeVehX  = t.dds_ApaSlotLeVehX;
        this->dds_ApaSlotLeVehY  = t.dds_ApaSlotLeVehY;
        this->dds_ApaSlotLeVehPsi  = t.dds_ApaSlotLeVehPsi;
        return (*this);
    }
    ////////////////////GetSerializedSize///////////////////////////////////////////////
    template <size_t ALIGN = 4U>
    size_t GetSerializedSize() const noexcept
    {
        return sizeof(DDSUSSApaSlot);
    }
    template <typename S>
    void Serialize(S& serializer) const
    {
        serializer <<  this->dds_ApaSlotLeID <<  this->dds_ApaSlotLeObj1Alpha <<  this->dds_ApaSlotLeObj1X<< this->dds_ApaSlotLeObj1Y
        << this->dds_ApaSlotLeObj2Alpha
        << this->dds_ApaSlotLeObj2X<< this->dds_ApaSlotLeObj2Y<< this->dds_ApaSlotLeSizeX
        << this->dds_ApaSlotLeSizeY<< this->dds_ApaSlotLeSts
        << this->dds_ApaSlotLeVehX<< this->dds_ApaSlotLeVehY<< this->dds_ApaSlotLeVehPsi;
    }

    template <typename D>
    void Deserialize(D& deserializer)
    {
        deserializer >>  this->dds_ApaSlotLeID >>this->dds_ApaSlotLeObj1Alpha >>this->dds_ApaSlotLeObj1X
        >> this->dds_ApaSlotLeObj1Y>> this->dds_ApaSlotLeObj2Alpha
        >> this->dds_ApaSlotLeObj2X>> this->dds_ApaSlotLeObj2Y>>this->dds_ApaSlotLeSizeX
        >> this->dds_ApaSlotLeSizeY>> this->dds_ApaSlotLeSts
        >> this->dds_ApaSlotLeVehX>> this->dds_ApaSlotLeVehY>>this->dds_ApaSlotLeVehPsi;
    }

    /////////////////////get////////////////////////////////////////////
    //get DDSUSSApaSlot funtion start
    holo::uint8_t  GetDdsApaslotleid() 
    {
        return this->dds_ApaSlotLeID;
    }
    holo::int8_t  GetDdsApaslotleobj1alpha() 
    {
        return this->dds_ApaSlotLeObj1Alpha;
    }
    holo::int16_t  GetDdsApaslotleobj1x() 
    {
        return this->dds_ApaSlotLeObj1X;
    }
    holo::int16_t  GetDdsApaslotleobj1y() 
    {
        return this->dds_ApaSlotLeObj1Y;
    }
    holo::int8_t  GetDdsApaslotleobj2alpha() 
    {
        return this->dds_ApaSlotLeObj2Alpha;
    }
    holo::int16_t  GetDdsApaslotleobj2x() 
    {
        return this->dds_ApaSlotLeObj2X;
    }
    holo::int16_t  GetDdsApaslotleobj2y() 
    {
        return this->dds_ApaSlotLeObj2Y;
    }
    holo::int16_t  GetDdsApaslotlesizex() 
    {
        return  this->dds_ApaSlotLeSizeX;
    }
    holo::uint16_t  GetDdsApaslotlesizey( ) 
    {
        return this->dds_ApaSlotLeSizeY;
    }
    holo::uint8_t  GetDdsApaslotlests() 
    {
        return this->dds_ApaSlotLeSts;
    }
    holo::int16_t  GetDdsApaslotlevehx() 
    {
        return this->dds_ApaSlotLeVehX;
    }
    holo::int16_t  GetDdsApaslotlevehy() 
    {
        return this->dds_ApaSlotLeVehY;
    }
     holo::float32_t  GetDdsApaslotlevehpsi() 
    {
        return this->dds_ApaSlotLeVehPsi;
    }
    ////////////////////set/////////////////////////////////////////////////////
    //fmh add slot set start
    void  SetDdsApaslotleid(const holo::uint8_t value) 
    {
        this->dds_ApaSlotLeID  = value;
    }
    void  SetDdsApaslotleobj1alpha(holo::int8_t value) 
    {
        this->dds_ApaSlotLeObj1Alpha  = value;  
    }
    void  SetDdsApaslotleobj1x(const  holo::int16_t value) 
    {
        this->dds_ApaSlotLeObj1X  = value;
    }
    void  SetDdsApaslotleobj1y(const  holo::int16_t value) 
    {
        this->dds_ApaSlotLeObj1Y  = value;
    }
    void  SetDdsApaslotleobj2alpha(holo::int8_t value) 
    {
        this-> dds_ApaSlotLeObj2Alpha  = value;
    }
    void  SetDdsApaslotleobj2x(const  holo::int16_t value) 
    {
        this->dds_ApaSlotLeObj2X  = value;
    }
    void  SetDdsApaslotleobj2y(const  holo::int16_t value)
    {
        this->dds_ApaSlotLeObj2Y  = value;
    }
    void  SetDdsApaslotlesizex(const holo::uint16_t value) 
    {
        this->dds_ApaSlotLeSizeX  = value;
    }
    void  SetDdsApaslotlesizey( const holo::uint16_t value) 
    {
        this->dds_ApaSlotLeSizeY  = value;
    }
    void  SetDdsApaslotlests(const holo::uint8_t value) 
    {
        this->dds_ApaSlotLeSts  = value;
    }
    void  SetDdsApaslotlevehpsi(const  holo::float32_t value) 
    {
        this-> dds_ApaSlotLeVehPsi  = value;
    }
    void  SetDdsApaslotlevehx(const  holo::int16_t value) 
    {
        this->dds_ApaSlotLeVehX  = value;
    }
    void  SetDdsApaslotlevehy(const  holo::int16_t value) 
    {
        this-> dds_ApaSlotLeVehY  = value;
    }
    //fmh add slot get end
public:
    //APA_04 to APA_07 same info
    holo::uint8_t   dds_ApaSlotLeID;
    holo::int8_t   dds_ApaSlotLeObj1Alpha;
    holo::int16_t  dds_ApaSlotLeObj1X;
    holo::int16_t  dds_ApaSlotLeObj1Y;
    holo::int8_t  dds_ApaSlotLeObj2Alpha;
    holo::int16_t  dds_ApaSlotLeObj2X;
    holo::int16_t  dds_ApaSlotLeObj2Y;
    holo::uint16_t  dds_ApaSlotLeSizeX;
    holo::uint16_t  dds_ApaSlotLeSizeY;
    holo::uint8_t  dds_ApaSlotLeSts;
    holo::int16_t  dds_ApaSlotLeVehX;
    holo::int16_t  dds_ApaSlotLeVehY;
    holo::float32_t  dds_ApaSlotLeVehPsi;
};//DDSUSSApaSlot

/////////////////////////DDSUSSApaParkSlot04To07////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////
class DDSUSSApaParkSlot04To07
{
public:
    DDSUSSApaParkSlot04To07()
    {
    }
    ~DDSUSSApaParkSlot04To07()
    {
    }
    ///////////////////////////////////////////////////////////////////////////////////
    ///////////////////////get////////////////////////////////////////////////
    Timestamp GetTimestamp() const noexcept
    {
        return  this->timestamp_;
    }
    /////////////////////////set////////////////////////////////////////////////
    void SetTimestamp(const Timestamp  timestamp)
    {
        this->timestamp_ = timestamp;
    }
    ///////////////////////////GetSerializedSize///////////
    template <size_t ALIGN = 4U>
    size_t GetSerializedSize() const noexcept
    {
         return timestamp_.GetSerializedSize<ALIGN>() +
                     holo::serialization::AlignedSize<ALIGN>(sizeof(DDSUSSApaSlot) *  SLOT_04TO07_ARRAY_NUMBER);
    }
    template <typename S>
    void Serialize(S& serializer) const
    {
       serializer <<  this->timestamp_ ;
        for (size_t index = 0U; index <  SLOT_04TO07_ARRAY_NUMBER; index++)
        {
            serializer << this->slot[index];
        }
        serializer << holo::serialization::align;
    }
    template <typename D>
    void Deserialize(D& deserializer)
    {
        deserializer >>  this->timestamp_ ;
        for (size_t index = 0U; index <  SLOT_04TO07_ARRAY_NUMBER; index++)
        {
            deserializer >>  this->slot[index];
        }
        deserializer >> holo::serialization::align;
    }

private:
    //APA_04,APA_05,APA_07 same info
    //fmh add the int
   //holo::uint16_t ddt_total_num_;
   //add the extern data
   holo::common::Timestamp timestamp_;  ///< Timestamp of this object.
public:
   DDSUSSApaSlot slot[SLOT_04TO07_ARRAY_NUMBER];

};//DDSUSSApaParkSlot04To07
}  // namespace details
}  // namespace common
}  // namespace holo
#endif//HOLO_C_COMMON_USS_DDS_APA_PARK_SLOT_04TO07_H_