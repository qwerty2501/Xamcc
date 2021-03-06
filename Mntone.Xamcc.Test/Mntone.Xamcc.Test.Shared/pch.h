#pragma once

#define NOMINMAX

#include <Windows.h>
#include <winapifamily.h>

#if WINAPI_FAMILY == WINAPI_FAMILY_PHONE_APP
#define PLATFORM_PREFIX( __NAME__ ) Wp ## __NAME__
#else
#define PLATFORM_PREFIX( __NAME__ ) Win ## __NAME__
#endif

#include <memory>
#include <array>
#include <vector>
#include <functional>
#include <random>

#include <collection.h>
#include <ppltasks.h>

#include "CppUnitTest.h"

namespace Microsoft { namespace VisualStudio { namespace CppUnitTestFramework {

	template<> static std::wstring ToString<::Windows::UI::Xaml::Visibility>( const ::Windows::UI::Xaml::Visibility& t ) { return t.ToString()->Data(); }
	template<> static std::wstring ToString<long long>( const long long& t ) { RETURN_WIDE_STRING( t ); }


} } }