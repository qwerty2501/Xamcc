#pragma once
#include <collection.h>

namespace std {
	template<>
	struct equal_to<::Windows::Foundation::DateTime>
	{
		bool operator()( const ::Windows::Foundation::DateTime& lhs, const ::Windows::Foundation::DateTime& rhs )
		{
			return lhs.UniversalTime == rhs.UniversalTime;
		}
	};
}

namespace Mntone { namespace Xamcc { 

	class DataProcessor
	{
	public:
		DataProcessor();

		::Platform::Collections::Vector<Windows::Foundation::DateTime>^ GetVector();
		::Platform::Collections::Vector<Windows::Foundation::DateTime>^ GetVector2();

	private:
		::Platform::Collections::Vector<Windows::Foundation::DateTime>^ Vector_;
		::Platform::Collections::Vector<Windows::Foundation::DateTime>^ Vector2_;

		::Windows::System::Threading::ThreadPoolTimer^ timer_;
	};

} }