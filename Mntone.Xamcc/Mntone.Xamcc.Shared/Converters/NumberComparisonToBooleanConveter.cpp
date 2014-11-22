#include "pch.h"
#include "NumberComparisonToBooleanConveter.h"

using namespace Platform;
using namespace std;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Interop;
using namespace Mntone::Xamcc::Converters;

namespace MXC = ::Mntone::Xamcc::Converters;

NumberComparisonToBooleanConveter::NumberComparisonToBooleanConveter()
{
	NumberType_ = MXC::NumberType::Int32;
	ComparisonType_ = MXC::ComparisonType::EqualTo;
	UpdateFunction();
}

Object^ NumberComparisonToBooleanConveter::Convert( Object^ value, TypeName /*targetType*/, Object^ parameter, String^ /*language*/ )
{
	return comparisonFunction_( value, dynamic_cast<String^>( parameter ) );
}

Object^ NumberComparisonToBooleanConveter::ConvertBack( Object^ /*value*/, TypeName /*targetType*/, Object^ /*parameter*/, String^ /*language*/ )
{
	throw ref new FailureException();
}

void NumberComparisonToBooleanConveter::NumberType::set( MXC::NumberType value )
{
	if( NumberType_ == value )
	{
		return;
	}
	NumberType_ = value;

	UpdateFunction();
}

void NumberComparisonToBooleanConveter::ComparisonType::set( MXC::ComparisonType value )
{
	if( ComparisonType_ == value )
	{
		return;
	}
	ComparisonType_ = value;

	UpdateFunction();
}


template<typename T>
T StringToNumber(Platform::String^ str);

template<>
static int16 StringToNumber<int16>(Platform::String^ str)
{
	return static_cast<int16>(_wtoi(str->Data()));
}

template<>
static uint16 StringToNumber<uint16>(Platform::String^ str)
{
	return static_cast<uint16>(wcstoul(str->Data(), nullptr, 10));
}

template<>
static uint32 StringToNumber<uint32>(Platform::String^ str)
{
	return static_cast<uint32>(wcstoul(str->Data(), nullptr, 10));
}

template<>
static int64 StringToNumber<int64>(Platform::String^ str)
{
	return static_cast<int64>(_wtoi64(str->Data()));
}

template<>
static uint64 StringToNumber<uint64>(Platform::String^ str)
{
	return static_cast<uint64>(wcstoull(str->Data(), nullptr, 10));
}

template<>
static float32 StringToNumber<float32>(Platform::String^ str)
{
	return static_cast<float32>(_wtof(str->Data()));
}

template<>
static float64 StringToNumber<float64>(Platform::String^ str)
{
	return _wtof(str->Data());
}

template<>
static int32 StringToNumber<int32>(Platform::String^ str)
{
	return _wtoi(str->Data());
}


template<typename T>
void NumberComparisonToBooleanConveter::InnerUpDateFunction()
{


	function<bool(T, T)> comparisonInnerFunc;
	switch (ComparisonType_)
	{
	case MXC::ComparisonType::NotEqualTo:
		comparisonInnerFunc = [](T value, T parameter) { return value != parameter; };
		break;

	case MXC::ComparisonType::LessThan:
		comparisonInnerFunc = [](T value, T parameter) { return value < parameter; };
		break;

	case MXC::ComparisonType::LessThanOrEqualTo:
		comparisonInnerFunc = [](T value, T parameter) { return value <= parameter; };
		break;

	case MXC::ComparisonType::GreaterThan:
		comparisonInnerFunc = [](T value, T parameter) { return value > parameter; };
		break;

	case MXC::ComparisonType::GreaterThanOrEqualTo:
		comparisonInnerFunc = [](T value, T parameter) { return value >= parameter; };
		break;

	case MXC::ComparisonType::EqualTo:
	default:
		comparisonInnerFunc = [](T value, T parameter) { return value == parameter; };
		break;
	}

	comparisonFunction_ = [comparisonInnerFunc](Object^ value, String^ parameter)
	{
		auto numberValue = dynamic_cast<IBox<T>^>(value);
		T numberParameter = parameter ? StringToNumber<T>(parameter) : 0;
		return numberValue ? comparisonInnerFunc(numberValue->Value, numberParameter) : DependencyProperty::UnsetValue;
	};
}


void NumberComparisonToBooleanConveter::UpdateFunction()
{
	switch( NumberType_ )
	{
	case MXC::NumberType::Int16:
	{
		InnerUpDateFunction<int16>();
		
		break;
	}

	case MXC::NumberType::UInt16:
	{
		InnerUpDateFunction<uint16>();

		break;
	}

	case MXC::NumberType::UInt32:
	{

		InnerUpDateFunction<uint32>();

		break;
	}

	case MXC::NumberType::Int64:
	{
		InnerUpDateFunction<int64>();

		
		break;
	}

	case MXC::NumberType::UInt64:
	{

		InnerUpDateFunction<uint64>();

		break;
	}

	case MXC::NumberType::Single:
	{
		InnerUpDateFunction<float32>();

		break;
	}

	case MXC::NumberType::Double:
	{
		InnerUpDateFunction<float64>();

		break;
	}

	case MXC::NumberType::Int32:
	default:
	{
		InnerUpDateFunction<int32>();

		break;
	}
	}
}