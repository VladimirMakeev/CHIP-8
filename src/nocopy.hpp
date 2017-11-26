
#ifndef NOCOPY_HPP
#define NOCOPY_HPP

class NonCopyable
{
protected:
	constexpr NonCopyable() = default;

	NonCopyable(const NonCopyable &) = delete;
	NonCopyable& operator=(const NonCopyable &) = delete;
};

#endif /* NOCOPY_HPP */

