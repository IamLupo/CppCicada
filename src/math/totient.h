#ifndef PRIME_TOTIENT_H
#define PRIME_TOTIENT_H

#include <array>
#include <cstdint>
#include <cstddef>

namespace math
{
	template <std::size_t N, std::size_t PRIME_COUNT>
	consteval std::array<uint32_t, PRIME_COUNT> make_prime_totients()
	{
		std::array<bool, N + 1> is_prime{};
		is_prime.fill(true);

		is_prime[0] = false;
		is_prime[1] = false;

		for (std::size_t i = 2; i * i <= N; ++i)
		{
			if (is_prime[i])
			{
				for (std::size_t j = i * i; j <= N; j += i)
					is_prime[j] = false;
			}
		}

		std::array<uint32_t, PRIME_COUNT> result{};

		std::size_t idx = 0;
		for (std::size_t i = 2; i <= N; ++i)
		{
			if (is_prime[i])
				result[idx++] = static_cast<uint32_t>(i - 1);
		}

		return result;
	}

	// 1000 -> 168 primes
	inline constexpr size_t total_prime_totients = 168;
	inline constexpr auto prime_totients_1000 = make_prime_totients<1000, total_prime_totients>();
}

#endif // PRIME_TOTIENT_H