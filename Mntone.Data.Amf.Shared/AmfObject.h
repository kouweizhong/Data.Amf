#pragma once
#include "IAmfObject.h"

namespace Mntone { namespace Data { namespace Amf {

	[Windows::Foundation::Metadata::DualApiPartition( version = NTDDI_WIN8 )]
	[Windows::Foundation::Metadata::MarshalingBehavior( Windows::Foundation::Metadata::MarshalingType::Agile )]
	[Windows::Foundation::Metadata::Threading( Windows::Foundation::Metadata::ThreadingModel::Both )]
	[Windows::Foundation::Metadata::WebHostHidden]
	public ref class AmfObject sealed:
		public IAmfObject,
		public Windows::Foundation::Collections::IMap<Platform::String^, IAmfValue^>
	{
	public:
		AmfObject();

		// IAmfValue
		virtual Platform::Array<uint8>^ Sequencify();
		virtual Platform::Array<uint8>^ Sequencify( AmfEncodingType type );
		virtual bool GetBoolean();
		virtual float64 GetNumber();
		virtual Platform::String^ GetString();
		virtual Windows::Foundation::DateTime GetDate();
		virtual Platform::Array<uint8>^ GetByteArray();
		virtual Windows::Foundation::Collections::IVector<int32>^ GetVectorInt();
		virtual Windows::Foundation::Collections::IVector<uint32>^ GetVectorUint();
		virtual Windows::Foundation::Collections::IVector<float64>^ GetVectorDouble();
		virtual Windows::Foundation::Collections::IVector<IAmfValue^>^ GetVectorObject();
		virtual AmfObject^ GetObject();
		virtual AmfArray^ GetArray();
		virtual AmfDictionary^ GetDictionary();

		// IAmfObject
		virtual IAmfValue^ GetNamedValue( Platform::String^ name );
		virtual void SetNamedValue( Platform::String^ name, IAmfValue^ value );
		virtual bool GetNamedBoolean( Platform::String^ name );
		virtual float64 GetNamedNumber( Platform::String^ name );
		virtual Platform::String^ GetNamedString( Platform::String^ name );
		virtual Windows::Foundation::DateTime GetNamedDate( Platform::String^ name );
		virtual Platform::Array<uint8>^ GetNamedByteArray( Platform::String^ name );
		virtual Windows::Foundation::Collections::IVector<int32>^ GetNamedVectorInt( Platform::String^ name );
		virtual Windows::Foundation::Collections::IVector<uint32>^ GetNamedVectorUint( Platform::String^ name );
		virtual Windows::Foundation::Collections::IVector<float64>^ GetNamedVectorDouble( Platform::String^ name );
		virtual Windows::Foundation::Collections::IVector<IAmfValue^>^ GetNamedVectorObject( Platform::String^ name );
		virtual AmfObject^ GetNamedObject( Platform::String^ name );
		virtual AmfArray^ GetNamedArray( Platform::String^ name );
		virtual AmfDictionary^ GetNamedDictionary( Platform::String^ name );

		// IIterator
		virtual Windows::Foundation::Collections::IIterator<Windows::Foundation::Collections::IKeyValuePair<Platform::String^, IAmfValue^>^>^ First();

		// IMap: read methods
		virtual IAmfValue^ Lookup( Platform::String^ key );
		virtual bool HasKey( Platform::String^ key );
		virtual Windows::Foundation::Collections::IMapView<Platform::String^, IAmfValue^>^ GetView();

		// IMap: write methods
		virtual bool Insert( Platform::String^ key, IAmfValue^ value );
		virtual void Remove( Platform::String^ key );
		virtual void Clear();

		// IStringable
#if !_WINDOWS_PHONE8
		virtual Platform::String^ ToString() override sealed;
#endif

		static AmfObject^ CreateEcmaArray();

		static AmfObject^ Parse( const Platform::Array<uint8>^ input );
		static AmfObject^ Parse( const Platform::Array<uint8>^ input, AmfEncodingType type );
		static bool TryParse( const Platform::Array<uint8>^ input, AmfObject^* result );
		static bool TryParse( const Platform::Array<uint8>^ input, AmfEncodingType type, AmfObject^* result );

	internal:
#if _WINDOWS_PHONE8
		void SetData( std::map<Platform::String^, IAmfValue^> data );
#else
		void SetData( std::unordered_map<Platform::String^, IAmfValue^> data );
#endif

	public:
		// IAmfValue
		property AmfValueType ValueType
		{
			virtual AmfValueType get() { return ValueType_; }
		}

		// IAmfObject
		property Platform::String^ ClassName
		{
			virtual Platform::String^ get() { return ClassName_; }
			virtual void set( Platform::String^ value ) { ClassName_ = std::move( value ); }
		}
		property bool Externalizable
		{
			virtual bool get() { return Externalizable_; }
			virtual void set( bool value ) { Externalizable_ = std::move( value ); }
		}

		// IMap
		property uint32 Size
		{
			virtual uint32 get() { return map_->Size; }
		}

	private:
		AmfValueType ValueType_;
#if _WINDOWS_PHONE8
		Platform::Collections::Map<Platform::String^, IAmfValue^>^ map_;
#else
		Platform::Collections::UnorderedMap<Platform::String^, IAmfValue^>^ map_;
#endif

		Platform::String^ ClassName_;
		bool Externalizable_;
	};

} } }
