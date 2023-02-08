#ifndef OBC_INTERVAL_HPP
#define OBC_INTERVAL_HPP

#include <Arduino.h>

#include <type_traits>

#include "result.hpp"

namespace obc {

class Interval {
   private:
    uint32_t interval{0};
    uint32_t current_time{0};
    uint32_t prev_time{0};

   public:
    explicit constexpr Interval(uint32_t interval) : interval{interval} {}

    const auto check()
    {
        const auto eval = [&]() { return current_time - prev_time < interval; };
        current_time = millis();
        if (eval()) { return false; }
        prev_time = current_time;
        return true;
    }

    template <typename Func, typename... Ts>
    constexpr auto execute(Func&& func, Ts&&... args)
    {
        static_assert(std::is_invocable_v<Func&&, Ts&&...>);

        using ret = std::optional<decltype(std::invoke(
            std::forward<Func>(func),
            std::forward<Ts>(args)...))>;

        if (check()) {
            return ret{std::invoke(
                std::forward<Func>(func),
                std::forward<Ts>(args)...)};
        }
        return ret{};
    }
};

}  // namespace obc

#endif