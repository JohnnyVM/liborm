#ifndef LIBORM_UTILS_ACBUFFER_HPP
#define LIBORM_UTILS_ACBUFFER_HPP

#include <type_traits>
#include <mutex>
#include <memory>
#include <variant>
#include <optional>
#include <deque>
#include <initializer_list>

template<typename C,
	std::enable_if_t<std::is_copy_constructible<C>::value, bool> = true>
class acbuffer
{
	public:
	using lock_strategy = std::variant<std::defer_lock_t, std::try_to_lock_t, std::adopt_lock_t>;
	acbuffer(std::initializer_list<C> const l) {
		for(C c : l) {
			container.push_back(std::make_unique<C>(c));
			observer.push_back({});
		}
	}

	inline std::optional<std::shared_ptr<C>>get() { // todo move this to atomic<shared in c++20
		std::scoped_lock lock(slock);
		unsigned i;
		for(i = 0; i < container.size() and not observer[i].expired(); i++);
		if(i == container.size()) {
			return std::nullopt; // Max open cursors
		}
		std::shared_ptr<C>res = std::make_shared<C>(*container[i].get());
		observer[i] = res;
		return res;
	}

	std::mutex slock;

	protected:
	std::deque<std::unique_ptr<C>> container;
	std::deque<std::weak_ptr<C>> observer;
};

#endif