#pragma once

#include <type_traits>

namespace MoonlightController {
	template <typename TComponent>
	struct Vector2D {
		static_assert(
			std::is_same<char, TComponent>::value ||
			std::is_same<unsigned char, TComponent>::value ||
			std::is_same<short, TComponent>::value ||
			std::is_same<unsigned short, TComponent>::value ||
			std::is_same<int, TComponent>::value ||
			std::is_same<unsigned int, TComponent>::value ||
			std::is_same<long, TComponent>::value ||
			std::is_same<unsigned long, TComponent>::value ||
			std::is_same<long long, TComponent>::value ||
			std::is_same<unsigned long long, TComponent>::value ||
			std::is_same<float, TComponent>::value ||
			std::is_same<double, TComponent>::value ||
			std::is_same<long double, TComponent>::value,
			"The specified 2D vector component type must be of a numeric type.");

		/// <summary>
		/// X component
		/// </summary>
		TComponent x;

		/// <summary>
		/// Y component
		/// </summary>
		TComponent y;

		constexpr inline Vector2D() : x(static_cast<TComponent>(0)), y(static_cast<TComponent>(0)) {
			// ...
		}

		constexpr inline Vector2D(int x, int y) : x(x), y(y) {
			// ...
		}
	};
}
