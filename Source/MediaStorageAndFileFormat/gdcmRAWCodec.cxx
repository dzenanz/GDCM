/*=========================================================================

  Program: GDCM (Grass Root DICOM). A DICOM library
  Module:  $URL$

  Copyright (c) 2006-2008 Mathieu Malaterre
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "gdcmRAWCodec.h"
#include "gdcmTransferSyntax.h"
#include "gdcmByteSwap.txx"
#include "gdcmDataElement.h"
#include "gdcmSequenceOfFragments.h"

#include <sstream>

namespace gdcm
{

class RAWInternals
{
public:
};

RAWCodec::RAWCodec()
{
  Internals = new RAWInternals;
}

RAWCodec::~RAWCodec()
{
  delete Internals;
}

bool RAWCodec::CanDecode(TransferSyntax const &ts)
{
  return ts == TransferSyntax::ImplicitVRLittleEndian
   || ts == TransferSyntax::ExplicitVRLittleEndian
   || ts == TransferSyntax::ExplicitVRBigEndian
   || ts == TransferSyntax::ImplicitVRBigEndianPrivateGE;
}

bool RAWCodec::Decode(DataElement const &in, DataElement &out)
{
  const ByteValue *bv = in.GetByteValue();
  assert( bv );
    std::stringstream is;
    is.write(bv->GetPointer(), bv->GetLength());
    std::stringstream os;
    bool r = Decode(is, os);
    assert( r );

    std::string str = os.str();
    std::string::size_type check = str.size();
 
    //memcpy(buffer, os.str().c_str(), check);  // FIXME
    out = in;
    out.SetByteValue( &str[0], str.size() );
    return r;
}

bool RAWCodec::Decode(std::istream &is, std::ostream &os)
{
  ImageCodec::Decode(is, os);
  return true;
}

} // end namespace gdcm
