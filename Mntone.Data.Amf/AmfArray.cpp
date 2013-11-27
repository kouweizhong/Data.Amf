#include "pch.h"
#include "AmfArray.h"
#include "amf0_parser.h"
#include "amf0_sequencer.h"
#include "amf3_parser.h"
#include "amf3_sequencer.h"
#include "com_exception_helper.h"

using namespace mntone::data::amf;
using namespace Mntone::Data::Amf;

AmfArray::AmfArray( void ) :
	ValueType_( AmfValueType::Array ),
	vector_( ref new Platform::Collections::Vector<IAmfValue^>() )
{ }

Platform::Array<uint8>^ AmfArray::Sequencify( void )
{
	return amf0_sequencer::sequencify( this );
}

Platform::Array<uint8>^ AmfArray::Sequencify( AmfEncodingType type )
{
	if( type == AmfEncodingType::Amf3 )
		return amf3_sequencer::sequencify( this );

	return amf0_sequencer::sequencify( this );
}

bool AmfArray::GetBoolean( void ) { throw com_exception_helper::create_invalid_operation_exception( L"Invalid value type." ); }
float64 AmfArray::GetNumber( void ) { throw com_exception_helper::create_invalid_operation_exception( L"Invalid value type." ); }
Platform::String^ AmfArray::GetString( void ) { throw com_exception_helper::create_invalid_operation_exception( L"Invalid value type." ); }
Windows::Foundation::DateTime AmfArray::GetDate( void ) { throw com_exception_helper::create_invalid_operation_exception( L"Invalid value type." ); }
Platform::Array<uint8>^ AmfArray::GetByteArray( void ) { throw com_exception_helper::create_invalid_operation_exception( L"Invalid value type." ); }
Windows::Foundation::Collections::IVector<int32>^ AmfArray::GetVectorInt( void ) { throw com_exception_helper::create_invalid_operation_exception( L"Invalid value type." ); }
Windows::Foundation::Collections::IVector<uint32>^ AmfArray::GetVectorUint( void ) { throw com_exception_helper::create_invalid_operation_exception( L"Invalid value type." ); }
Windows::Foundation::Collections::IVector<float64>^ AmfArray::GetVectorDouble( void ) { throw com_exception_helper::create_invalid_operation_exception( L"Invalid value type." ); }
Windows::Foundation::Collections::IVector<IAmfValue^>^ AmfArray::GetVectorObject( void ) { throw com_exception_helper::create_invalid_operation_exception( L"Invalid value type." ); }
AmfObject^ AmfArray::GetObject( void ) { throw com_exception_helper::create_invalid_operation_exception( L"Invalid value type." ); }

AmfArray^ AmfArray::GetArray( void )
{
	if( ValueType_ != AmfValueType::Array )
		throw com_exception_helper::create_invalid_operation_exception( L"Invalid value type." );

	return safe_cast<AmfArray^>( this );
}

bool AmfArray::GetBooleanAt( uint32 index ) { return vector_->GetAt( index )->GetBoolean(); }
float64 AmfArray::GetNumberAt( uint32 index ) { return vector_->GetAt( index )->GetNumber(); }
Platform::String^ AmfArray::GetStringAt( uint32 index ) { return vector_->GetAt( index )->GetString(); }
Windows::Foundation::DateTime AmfArray::GetDateAt( uint32 index ) { return vector_->GetAt( index )->GetDate(); }
Platform::Array<uint8>^ AmfArray::GetByteArrayAt( uint32 index ) { return vector_->GetAt( index )->GetByteArray(); }
Windows::Foundation::Collections::IVector<int32>^ AmfArray::GetVectorIntAt( uint32 index ) { return vector_->GetAt( index )->GetVectorInt(); }
Windows::Foundation::Collections::IVector<uint32>^ AmfArray::GetVectorUintAt( uint32 index ) { return vector_->GetAt( index )->GetVectorUint(); }
Windows::Foundation::Collections::IVector<float64>^ AmfArray::GetVectorDoubleAt( uint32 index ) { return vector_->GetAt( index )->GetVectorDouble(); }
Windows::Foundation::Collections::IVector<IAmfValue^>^ AmfArray::GetVectorObjectAt( uint32 index ) { return vector_->GetAt( index )->GetVectorObject(); }
AmfObject^ AmfArray::GetObjectAt( uint32 index ) { return vector_->GetAt( index )->GetObject(); }
AmfArray^ AmfArray::GetArrayAt( uint32 index ) { return vector_->GetAt( index )->GetArray(); }

Windows::Foundation::Collections::IIterator<IAmfValue^>^ AmfArray::First( void ) { return vector_->First(); }

IAmfValue^ AmfArray::GetAt( uint32 index ) { return vector_->GetAt( index ); }
Windows::Foundation::Collections::IVectorView<IAmfValue^>^ AmfArray::GetView( void ) { return vector_->GetView(); }
bool AmfArray::IndexOf( IAmfValue^ value, uint32 *index ) { return vector_->IndexOf( value, index ); }

void AmfArray::SetAt( uint32 index, IAmfValue^ value ) { vector_->SetAt( index, value ); }
void AmfArray::InsertAt( uint32 index, IAmfValue^ value ) { vector_->InsertAt( index, value ); }
void AmfArray::RemoveAt( uint32 index ) { vector_->RemoveAt( index ); }
void AmfArray::Append( IAmfValue^ value ) { vector_->Append( value ); }
void AmfArray::RemoveAtEnd( void ) { vector_->RemoveAtEnd(); }
void AmfArray::Clear( void ) { vector_->Clear(); }

uint32 AmfArray::GetMany( uint32 startIndex, Platform::WriteOnlyArray<IAmfValue^>^ items ) { return vector_->GetMany( startIndex, items ); }
void AmfArray::ReplaceAll( const Platform::Array<IAmfValue^>^ items ) { vector_->ReplaceAll( items ); }

#if !_WINDOWS_PHONE
Platform::String^ AmfArray::ToString( void )
{
	std::wstringstream buf;
	buf << '[';
	for( const auto& item : vector_ )
	{
		const auto& out = item->ToString();
		buf.write( out->Data(), out->Length() );
		buf.write( L", ", 2 );
	}
	auto str = buf.str();
	const auto& length = str.length();
	if( length != 1 )
		str.erase( length - 2 );
	str += L']';
	return ref new Platform::String( str.c_str(), static_cast<uint32>( str.length() ) );
}
#endif

AmfArray^ AmfArray::Parse( const Platform::Array<uint8>^ input )
{
	return reinterpret_cast<AmfArray^>( amf0_parser::parse( input ) );
}

AmfArray^ AmfArray::Parse( const Platform::Array<uint8>^ input, AmfEncodingType type )
{
	if( type == AmfEncodingType::Amf3 )
		return reinterpret_cast<AmfArray^>( amf3_parser::parse( input ) );

	return reinterpret_cast<AmfArray^>( amf0_parser::parse( input ) );
}

bool AmfArray::TryParse( const Platform::Array<uint8>^ input, AmfArray^* result )
{
	auto buf = reinterpret_cast<IAmfValue^*>( result );
	return amf0_parser::try_parse( input, buf );
}

bool AmfArray::TryParse( const Platform::Array<uint8>^ input, AmfEncodingType type, AmfArray^* result )
{
	auto buf = reinterpret_cast<IAmfValue^*>( result );
	if( type == AmfEncodingType::Amf3 )
		return amf3_parser::try_parse( input, buf );

	return amf0_parser::try_parse( input, buf );
}

void AmfArray::SetData( std::vector<IAmfValue^> data )
{
	vector_ = ref new Platform::Collections::Vector<IAmfValue^>( std::move( data ) );
}