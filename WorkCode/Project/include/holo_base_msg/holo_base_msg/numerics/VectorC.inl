// -*- C++ -*-
// $Id$

/**
 * Code generated by the The ACE ORB (TAO) IDL Compiler v2.2a_p19
 * TAO and the TAO IDL Compiler have been developed by:
 *       Center for Distributed Object Computing
 *       Washington University
 *       St. Louis, MO
 *       USA
 *       http://www.cs.wustl.edu/~schmidt/doc-center.html
 * and
 *       Distributed Object Computing Laboratory
 *       University of California at Irvine
 *       Irvine, CA
 *       USA
 * and
 *       Institute for Software Integrated Systems
 *       Vanderbilt University
 *       Nashville, TN
 *       USA
 *       http://www.isis.vanderbilt.edu/
 *
 * Information about TAO is available at:
 *     http://www.cs.wustl.edu/~schmidt/TAO.html
 **/


// TAO_IDL - Generated from
// be/be_visitor_array/array_ci.cpp:150

ACE_INLINE
void
TAO::Array_Traits<holo_base_msg::numerics::Vector2d_forany>::free (
    holo_base_msg::numerics::Vector2d_slice * _tao_slice
  )
{
  holo_base_msg::numerics::Vector2d_free (_tao_slice);
}

ACE_INLINE
holo_base_msg::numerics::Vector2d_slice *
TAO::Array_Traits<holo_base_msg::numerics::Vector2d_forany>::dup (
    const holo_base_msg::numerics::Vector2d_slice * _tao_slice
  )
{
  return holo_base_msg::numerics::Vector2d_dup (_tao_slice);
}

ACE_INLINE
void
TAO::Array_Traits<holo_base_msg::numerics::Vector2d_forany>::copy (
    holo_base_msg::numerics::Vector2d_slice * _tao_to,
    const holo_base_msg::numerics::Vector2d_slice * _tao_from
  )
{
  holo_base_msg::numerics::Vector2d_copy (_tao_to, _tao_from);
}

ACE_INLINE
void
TAO::Array_Traits<holo_base_msg::numerics::Vector2d_forany>::zero (
    holo_base_msg::numerics::Vector2d_slice * _tao_slice
  )
{
  // Zero each individual element.
  for ( ::CORBA::ULong i0 = 0; i0 < 2; ++i0)
    {
      _tao_slice[i0] = holo_base_msg::core::float64_t ();
    }
}

ACE_INLINE
holo_base_msg::numerics::Vector2d_slice *
TAO::Array_Traits<holo_base_msg::numerics::Vector2d_forany>::alloc (void)
{
  return holo_base_msg::numerics::Vector2d_alloc ();
}


// TAO_IDL - Generated from
// be/be_visitor_array/array_ci.cpp:150

ACE_INLINE
void
TAO::Array_Traits<holo_base_msg::numerics::Vector3d_forany>::free (
    holo_base_msg::numerics::Vector3d_slice * _tao_slice
  )
{
  holo_base_msg::numerics::Vector3d_free (_tao_slice);
}

ACE_INLINE
holo_base_msg::numerics::Vector3d_slice *
TAO::Array_Traits<holo_base_msg::numerics::Vector3d_forany>::dup (
    const holo_base_msg::numerics::Vector3d_slice * _tao_slice
  )
{
  return holo_base_msg::numerics::Vector3d_dup (_tao_slice);
}

ACE_INLINE
void
TAO::Array_Traits<holo_base_msg::numerics::Vector3d_forany>::copy (
    holo_base_msg::numerics::Vector3d_slice * _tao_to,
    const holo_base_msg::numerics::Vector3d_slice * _tao_from
  )
{
  holo_base_msg::numerics::Vector3d_copy (_tao_to, _tao_from);
}

ACE_INLINE
void
TAO::Array_Traits<holo_base_msg::numerics::Vector3d_forany>::zero (
    holo_base_msg::numerics::Vector3d_slice * _tao_slice
  )
{
  // Zero each individual element.
  for ( ::CORBA::ULong i0 = 0; i0 < 3; ++i0)
    {
      _tao_slice[i0] = holo_base_msg::core::float64_t ();
    }
}

ACE_INLINE
holo_base_msg::numerics::Vector3d_slice *
TAO::Array_Traits<holo_base_msg::numerics::Vector3d_forany>::alloc (void)
{
  return holo_base_msg::numerics::Vector3d_alloc ();
}


// TAO_IDL - Generated from
// be/be_visitor_array/array_ci.cpp:150

ACE_INLINE
void
TAO::Array_Traits<holo_base_msg::numerics::Vector4d_forany>::free (
    holo_base_msg::numerics::Vector4d_slice * _tao_slice
  )
{
  holo_base_msg::numerics::Vector4d_free (_tao_slice);
}

ACE_INLINE
holo_base_msg::numerics::Vector4d_slice *
TAO::Array_Traits<holo_base_msg::numerics::Vector4d_forany>::dup (
    const holo_base_msg::numerics::Vector4d_slice * _tao_slice
  )
{
  return holo_base_msg::numerics::Vector4d_dup (_tao_slice);
}

ACE_INLINE
void
TAO::Array_Traits<holo_base_msg::numerics::Vector4d_forany>::copy (
    holo_base_msg::numerics::Vector4d_slice * _tao_to,
    const holo_base_msg::numerics::Vector4d_slice * _tao_from
  )
{
  holo_base_msg::numerics::Vector4d_copy (_tao_to, _tao_from);
}

ACE_INLINE
void
TAO::Array_Traits<holo_base_msg::numerics::Vector4d_forany>::zero (
    holo_base_msg::numerics::Vector4d_slice * _tao_slice
  )
{
  // Zero each individual element.
  for ( ::CORBA::ULong i0 = 0; i0 < 4; ++i0)
    {
      _tao_slice[i0] = holo_base_msg::core::float64_t ();
    }
}

ACE_INLINE
holo_base_msg::numerics::Vector4d_slice *
TAO::Array_Traits<holo_base_msg::numerics::Vector4d_forany>::alloc (void)
{
  return holo_base_msg::numerics::Vector4d_alloc ();
}


// TAO_IDL - Generated from
// be/be_visitor_array/array_ci.cpp:150

ACE_INLINE
void
TAO::Array_Traits<holo_base_msg::numerics::Vector5d_forany>::free (
    holo_base_msg::numerics::Vector5d_slice * _tao_slice
  )
{
  holo_base_msg::numerics::Vector5d_free (_tao_slice);
}

ACE_INLINE
holo_base_msg::numerics::Vector5d_slice *
TAO::Array_Traits<holo_base_msg::numerics::Vector5d_forany>::dup (
    const holo_base_msg::numerics::Vector5d_slice * _tao_slice
  )
{
  return holo_base_msg::numerics::Vector5d_dup (_tao_slice);
}

ACE_INLINE
void
TAO::Array_Traits<holo_base_msg::numerics::Vector5d_forany>::copy (
    holo_base_msg::numerics::Vector5d_slice * _tao_to,
    const holo_base_msg::numerics::Vector5d_slice * _tao_from
  )
{
  holo_base_msg::numerics::Vector5d_copy (_tao_to, _tao_from);
}

ACE_INLINE
void
TAO::Array_Traits<holo_base_msg::numerics::Vector5d_forany>::zero (
    holo_base_msg::numerics::Vector5d_slice * _tao_slice
  )
{
  // Zero each individual element.
  for ( ::CORBA::ULong i0 = 0; i0 < 5; ++i0)
    {
      _tao_slice[i0] = holo_base_msg::core::float64_t ();
    }
}

ACE_INLINE
holo_base_msg::numerics::Vector5d_slice *
TAO::Array_Traits<holo_base_msg::numerics::Vector5d_forany>::alloc (void)
{
  return holo_base_msg::numerics::Vector5d_alloc ();
}


// TAO_IDL - Generated from
// be/be_visitor_array/array_ci.cpp:150

ACE_INLINE
void
TAO::Array_Traits<holo_base_msg::numerics::Vector6d_forany>::free (
    holo_base_msg::numerics::Vector6d_slice * _tao_slice
  )
{
  holo_base_msg::numerics::Vector6d_free (_tao_slice);
}

ACE_INLINE
holo_base_msg::numerics::Vector6d_slice *
TAO::Array_Traits<holo_base_msg::numerics::Vector6d_forany>::dup (
    const holo_base_msg::numerics::Vector6d_slice * _tao_slice
  )
{
  return holo_base_msg::numerics::Vector6d_dup (_tao_slice);
}

ACE_INLINE
void
TAO::Array_Traits<holo_base_msg::numerics::Vector6d_forany>::copy (
    holo_base_msg::numerics::Vector6d_slice * _tao_to,
    const holo_base_msg::numerics::Vector6d_slice * _tao_from
  )
{
  holo_base_msg::numerics::Vector6d_copy (_tao_to, _tao_from);
}

ACE_INLINE
void
TAO::Array_Traits<holo_base_msg::numerics::Vector6d_forany>::zero (
    holo_base_msg::numerics::Vector6d_slice * _tao_slice
  )
{
  // Zero each individual element.
  for ( ::CORBA::ULong i0 = 0; i0 < 6; ++i0)
    {
      _tao_slice[i0] = holo_base_msg::core::float64_t ();
    }
}

ACE_INLINE
holo_base_msg::numerics::Vector6d_slice *
TAO::Array_Traits<holo_base_msg::numerics::Vector6d_forany>::alloc (void)
{
  return holo_base_msg::numerics::Vector6d_alloc ();
}


// TAO_IDL - Generated from
// be/be_visitor_array/array_ci.cpp:150

ACE_INLINE
void
TAO::Array_Traits<holo_base_msg::numerics::Vector7d_forany>::free (
    holo_base_msg::numerics::Vector7d_slice * _tao_slice
  )
{
  holo_base_msg::numerics::Vector7d_free (_tao_slice);
}

ACE_INLINE
holo_base_msg::numerics::Vector7d_slice *
TAO::Array_Traits<holo_base_msg::numerics::Vector7d_forany>::dup (
    const holo_base_msg::numerics::Vector7d_slice * _tao_slice
  )
{
  return holo_base_msg::numerics::Vector7d_dup (_tao_slice);
}

ACE_INLINE
void
TAO::Array_Traits<holo_base_msg::numerics::Vector7d_forany>::copy (
    holo_base_msg::numerics::Vector7d_slice * _tao_to,
    const holo_base_msg::numerics::Vector7d_slice * _tao_from
  )
{
  holo_base_msg::numerics::Vector7d_copy (_tao_to, _tao_from);
}

ACE_INLINE
void
TAO::Array_Traits<holo_base_msg::numerics::Vector7d_forany>::zero (
    holo_base_msg::numerics::Vector7d_slice * _tao_slice
  )
{
  // Zero each individual element.
  for ( ::CORBA::ULong i0 = 0; i0 < 7; ++i0)
    {
      _tao_slice[i0] = holo_base_msg::core::float64_t ();
    }
}

ACE_INLINE
holo_base_msg::numerics::Vector7d_slice *
TAO::Array_Traits<holo_base_msg::numerics::Vector7d_forany>::alloc (void)
{
  return holo_base_msg::numerics::Vector7d_alloc ();
}


// TAO_IDL - Generated from
// be/be_visitor_array/array_ci.cpp:150

ACE_INLINE
void
TAO::Array_Traits<holo_base_msg::numerics::Vector8d_forany>::free (
    holo_base_msg::numerics::Vector8d_slice * _tao_slice
  )
{
  holo_base_msg::numerics::Vector8d_free (_tao_slice);
}

ACE_INLINE
holo_base_msg::numerics::Vector8d_slice *
TAO::Array_Traits<holo_base_msg::numerics::Vector8d_forany>::dup (
    const holo_base_msg::numerics::Vector8d_slice * _tao_slice
  )
{
  return holo_base_msg::numerics::Vector8d_dup (_tao_slice);
}

ACE_INLINE
void
TAO::Array_Traits<holo_base_msg::numerics::Vector8d_forany>::copy (
    holo_base_msg::numerics::Vector8d_slice * _tao_to,
    const holo_base_msg::numerics::Vector8d_slice * _tao_from
  )
{
  holo_base_msg::numerics::Vector8d_copy (_tao_to, _tao_from);
}

ACE_INLINE
void
TAO::Array_Traits<holo_base_msg::numerics::Vector8d_forany>::zero (
    holo_base_msg::numerics::Vector8d_slice * _tao_slice
  )
{
  // Zero each individual element.
  for ( ::CORBA::ULong i0 = 0; i0 < 8; ++i0)
    {
      _tao_slice[i0] = holo_base_msg::core::float64_t ();
    }
}

ACE_INLINE
holo_base_msg::numerics::Vector8d_slice *
TAO::Array_Traits<holo_base_msg::numerics::Vector8d_forany>::alloc (void)
{
  return holo_base_msg::numerics::Vector8d_alloc ();
}


// TAO_IDL - Generated from
// be/be_visitor_array/array_ci.cpp:150

ACE_INLINE
void
TAO::Array_Traits<holo_base_msg::numerics::Vector2f_forany>::free (
    holo_base_msg::numerics::Vector2f_slice * _tao_slice
  )
{
  holo_base_msg::numerics::Vector2f_free (_tao_slice);
}

ACE_INLINE
holo_base_msg::numerics::Vector2f_slice *
TAO::Array_Traits<holo_base_msg::numerics::Vector2f_forany>::dup (
    const holo_base_msg::numerics::Vector2f_slice * _tao_slice
  )
{
  return holo_base_msg::numerics::Vector2f_dup (_tao_slice);
}

ACE_INLINE
void
TAO::Array_Traits<holo_base_msg::numerics::Vector2f_forany>::copy (
    holo_base_msg::numerics::Vector2f_slice * _tao_to,
    const holo_base_msg::numerics::Vector2f_slice * _tao_from
  )
{
  holo_base_msg::numerics::Vector2f_copy (_tao_to, _tao_from);
}

ACE_INLINE
void
TAO::Array_Traits<holo_base_msg::numerics::Vector2f_forany>::zero (
    holo_base_msg::numerics::Vector2f_slice * _tao_slice
  )
{
  // Zero each individual element.
  for ( ::CORBA::ULong i0 = 0; i0 < 2; ++i0)
    {
      _tao_slice[i0] = holo_base_msg::core::float32_t ();
    }
}

ACE_INLINE
holo_base_msg::numerics::Vector2f_slice *
TAO::Array_Traits<holo_base_msg::numerics::Vector2f_forany>::alloc (void)
{
  return holo_base_msg::numerics::Vector2f_alloc ();
}


// TAO_IDL - Generated from
// be/be_visitor_array/array_ci.cpp:150

ACE_INLINE
void
TAO::Array_Traits<holo_base_msg::numerics::Vector3f_forany>::free (
    holo_base_msg::numerics::Vector3f_slice * _tao_slice
  )
{
  holo_base_msg::numerics::Vector3f_free (_tao_slice);
}

ACE_INLINE
holo_base_msg::numerics::Vector3f_slice *
TAO::Array_Traits<holo_base_msg::numerics::Vector3f_forany>::dup (
    const holo_base_msg::numerics::Vector3f_slice * _tao_slice
  )
{
  return holo_base_msg::numerics::Vector3f_dup (_tao_slice);
}

ACE_INLINE
void
TAO::Array_Traits<holo_base_msg::numerics::Vector3f_forany>::copy (
    holo_base_msg::numerics::Vector3f_slice * _tao_to,
    const holo_base_msg::numerics::Vector3f_slice * _tao_from
  )
{
  holo_base_msg::numerics::Vector3f_copy (_tao_to, _tao_from);
}

ACE_INLINE
void
TAO::Array_Traits<holo_base_msg::numerics::Vector3f_forany>::zero (
    holo_base_msg::numerics::Vector3f_slice * _tao_slice
  )
{
  // Zero each individual element.
  for ( ::CORBA::ULong i0 = 0; i0 < 3; ++i0)
    {
      _tao_slice[i0] = holo_base_msg::core::float32_t ();
    }
}

ACE_INLINE
holo_base_msg::numerics::Vector3f_slice *
TAO::Array_Traits<holo_base_msg::numerics::Vector3f_forany>::alloc (void)
{
  return holo_base_msg::numerics::Vector3f_alloc ();
}


// TAO_IDL - Generated from
// be/be_visitor_array/array_ci.cpp:150

ACE_INLINE
void
TAO::Array_Traits<holo_base_msg::numerics::Vector4f_forany>::free (
    holo_base_msg::numerics::Vector4f_slice * _tao_slice
  )
{
  holo_base_msg::numerics::Vector4f_free (_tao_slice);
}

ACE_INLINE
holo_base_msg::numerics::Vector4f_slice *
TAO::Array_Traits<holo_base_msg::numerics::Vector4f_forany>::dup (
    const holo_base_msg::numerics::Vector4f_slice * _tao_slice
  )
{
  return holo_base_msg::numerics::Vector4f_dup (_tao_slice);
}

ACE_INLINE
void
TAO::Array_Traits<holo_base_msg::numerics::Vector4f_forany>::copy (
    holo_base_msg::numerics::Vector4f_slice * _tao_to,
    const holo_base_msg::numerics::Vector4f_slice * _tao_from
  )
{
  holo_base_msg::numerics::Vector4f_copy (_tao_to, _tao_from);
}

ACE_INLINE
void
TAO::Array_Traits<holo_base_msg::numerics::Vector4f_forany>::zero (
    holo_base_msg::numerics::Vector4f_slice * _tao_slice
  )
{
  // Zero each individual element.
  for ( ::CORBA::ULong i0 = 0; i0 < 4; ++i0)
    {
      _tao_slice[i0] = holo_base_msg::core::float32_t ();
    }
}

ACE_INLINE
holo_base_msg::numerics::Vector4f_slice *
TAO::Array_Traits<holo_base_msg::numerics::Vector4f_forany>::alloc (void)
{
  return holo_base_msg::numerics::Vector4f_alloc ();
}


// TAO_IDL - Generated from
// be/be_visitor_array/array_ci.cpp:150

ACE_INLINE
void
TAO::Array_Traits<holo_base_msg::numerics::Vector5f_forany>::free (
    holo_base_msg::numerics::Vector5f_slice * _tao_slice
  )
{
  holo_base_msg::numerics::Vector5f_free (_tao_slice);
}

ACE_INLINE
holo_base_msg::numerics::Vector5f_slice *
TAO::Array_Traits<holo_base_msg::numerics::Vector5f_forany>::dup (
    const holo_base_msg::numerics::Vector5f_slice * _tao_slice
  )
{
  return holo_base_msg::numerics::Vector5f_dup (_tao_slice);
}

ACE_INLINE
void
TAO::Array_Traits<holo_base_msg::numerics::Vector5f_forany>::copy (
    holo_base_msg::numerics::Vector5f_slice * _tao_to,
    const holo_base_msg::numerics::Vector5f_slice * _tao_from
  )
{
  holo_base_msg::numerics::Vector5f_copy (_tao_to, _tao_from);
}

ACE_INLINE
void
TAO::Array_Traits<holo_base_msg::numerics::Vector5f_forany>::zero (
    holo_base_msg::numerics::Vector5f_slice * _tao_slice
  )
{
  // Zero each individual element.
  for ( ::CORBA::ULong i0 = 0; i0 < 5; ++i0)
    {
      _tao_slice[i0] = holo_base_msg::core::float32_t ();
    }
}

ACE_INLINE
holo_base_msg::numerics::Vector5f_slice *
TAO::Array_Traits<holo_base_msg::numerics::Vector5f_forany>::alloc (void)
{
  return holo_base_msg::numerics::Vector5f_alloc ();
}


// TAO_IDL - Generated from
// be/be_visitor_array/array_ci.cpp:150

ACE_INLINE
void
TAO::Array_Traits<holo_base_msg::numerics::Vector6f_forany>::free (
    holo_base_msg::numerics::Vector6f_slice * _tao_slice
  )
{
  holo_base_msg::numerics::Vector6f_free (_tao_slice);
}

ACE_INLINE
holo_base_msg::numerics::Vector6f_slice *
TAO::Array_Traits<holo_base_msg::numerics::Vector6f_forany>::dup (
    const holo_base_msg::numerics::Vector6f_slice * _tao_slice
  )
{
  return holo_base_msg::numerics::Vector6f_dup (_tao_slice);
}

ACE_INLINE
void
TAO::Array_Traits<holo_base_msg::numerics::Vector6f_forany>::copy (
    holo_base_msg::numerics::Vector6f_slice * _tao_to,
    const holo_base_msg::numerics::Vector6f_slice * _tao_from
  )
{
  holo_base_msg::numerics::Vector6f_copy (_tao_to, _tao_from);
}

ACE_INLINE
void
TAO::Array_Traits<holo_base_msg::numerics::Vector6f_forany>::zero (
    holo_base_msg::numerics::Vector6f_slice * _tao_slice
  )
{
  // Zero each individual element.
  for ( ::CORBA::ULong i0 = 0; i0 < 6; ++i0)
    {
      _tao_slice[i0] = holo_base_msg::core::float32_t ();
    }
}

ACE_INLINE
holo_base_msg::numerics::Vector6f_slice *
TAO::Array_Traits<holo_base_msg::numerics::Vector6f_forany>::alloc (void)
{
  return holo_base_msg::numerics::Vector6f_alloc ();
}


// TAO_IDL - Generated from
// be/be_visitor_array/array_ci.cpp:150

ACE_INLINE
void
TAO::Array_Traits<holo_base_msg::numerics::Vector7f_forany>::free (
    holo_base_msg::numerics::Vector7f_slice * _tao_slice
  )
{
  holo_base_msg::numerics::Vector7f_free (_tao_slice);
}

ACE_INLINE
holo_base_msg::numerics::Vector7f_slice *
TAO::Array_Traits<holo_base_msg::numerics::Vector7f_forany>::dup (
    const holo_base_msg::numerics::Vector7f_slice * _tao_slice
  )
{
  return holo_base_msg::numerics::Vector7f_dup (_tao_slice);
}

ACE_INLINE
void
TAO::Array_Traits<holo_base_msg::numerics::Vector7f_forany>::copy (
    holo_base_msg::numerics::Vector7f_slice * _tao_to,
    const holo_base_msg::numerics::Vector7f_slice * _tao_from
  )
{
  holo_base_msg::numerics::Vector7f_copy (_tao_to, _tao_from);
}

ACE_INLINE
void
TAO::Array_Traits<holo_base_msg::numerics::Vector7f_forany>::zero (
    holo_base_msg::numerics::Vector7f_slice * _tao_slice
  )
{
  // Zero each individual element.
  for ( ::CORBA::ULong i0 = 0; i0 < 7; ++i0)
    {
      _tao_slice[i0] = holo_base_msg::core::float32_t ();
    }
}

ACE_INLINE
holo_base_msg::numerics::Vector7f_slice *
TAO::Array_Traits<holo_base_msg::numerics::Vector7f_forany>::alloc (void)
{
  return holo_base_msg::numerics::Vector7f_alloc ();
}


// TAO_IDL - Generated from
// be/be_visitor_array/array_ci.cpp:150

ACE_INLINE
void
TAO::Array_Traits<holo_base_msg::numerics::Vector8f_forany>::free (
    holo_base_msg::numerics::Vector8f_slice * _tao_slice
  )
{
  holo_base_msg::numerics::Vector8f_free (_tao_slice);
}

ACE_INLINE
holo_base_msg::numerics::Vector8f_slice *
TAO::Array_Traits<holo_base_msg::numerics::Vector8f_forany>::dup (
    const holo_base_msg::numerics::Vector8f_slice * _tao_slice
  )
{
  return holo_base_msg::numerics::Vector8f_dup (_tao_slice);
}

ACE_INLINE
void
TAO::Array_Traits<holo_base_msg::numerics::Vector8f_forany>::copy (
    holo_base_msg::numerics::Vector8f_slice * _tao_to,
    const holo_base_msg::numerics::Vector8f_slice * _tao_from
  )
{
  holo_base_msg::numerics::Vector8f_copy (_tao_to, _tao_from);
}

ACE_INLINE
void
TAO::Array_Traits<holo_base_msg::numerics::Vector8f_forany>::zero (
    holo_base_msg::numerics::Vector8f_slice * _tao_slice
  )
{
  // Zero each individual element.
  for ( ::CORBA::ULong i0 = 0; i0 < 8; ++i0)
    {
      _tao_slice[i0] = holo_base_msg::core::float32_t ();
    }
}

ACE_INLINE
holo_base_msg::numerics::Vector8f_slice *
TAO::Array_Traits<holo_base_msg::numerics::Vector8f_forany>::alloc (void)
{
  return holo_base_msg::numerics::Vector8f_alloc ();
}


