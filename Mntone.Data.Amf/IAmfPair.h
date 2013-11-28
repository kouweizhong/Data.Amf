#pragma once
#include "IAmfArray.h"

namespace Mntone { namespace Data { namespace Amf {

	[Windows::Foundation::Metadata::WebHostHidden]
	public interface class IAmfPair:
		public Windows::Foundation::Collections::IKeyValuePair<IAmfValue^, IAmfValue^>
	{
		property AmfValueType KeyType
		{
			AmfValueType get( void );
		}
		property IAmfValue^ Key
		{
			void set( IAmfValue^ value );
		}
		property AmfValueType ValueType
		{
			AmfValueType get( void );
		}
		property IAmfValue^ Value
		{
			void set( IAmfValue^ value );
		}
	};

} } }
