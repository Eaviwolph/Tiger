/// \file
// Range v3 library
//
//  Copyright Eric Niebler 2013-present
//
//  Use, modification and distribution is subject to the
//  Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
// Project home: https://github.com/ericniebler/range-v3
//

#ifndef RANGES_V3_VIEW_UNIQUE_HPP
#define RANGES_V3_VIEW_UNIQUE_HPP

#include <utility>

#include <meta/meta.hpp>

#include <range/v3/range_fwd.hpp>

#include <range/v3/functional/bind_back.hpp>
#include <range/v3/functional/not_fn.hpp>
#include <range/v3/utility/static_const.hpp>
#include <range/v3/view/adjacent_filter.hpp>
#include <range/v3/view/all.hpp>
#include <range/v3/view/view.hpp>

#include <range/v3/detail/disable_warnings.hpp>

namespace ranges
{
    /// \addtogroup group-views
    /// @{
    namespace views
    {
        struct unique_base_fn
        {
            template<typename Rng, typename C = equal_to>
            constexpr auto operator()(Rng && rng, C pred = {}) const
                -> CPP_ret(adjacent_filter_view<all_t<Rng>, logical_negate<C>>)( //
                    requires viewable_range<Rng> && forward_range<Rng> &&
                        indirect_relation<C, iterator_t<Rng>>)
            {
                return {all(static_cast<Rng &&>(rng)), not_fn(pred)};
            }
        };

        struct unique_fn : unique_base_fn
        {
            using unique_base_fn::operator();

            template<typename C>
            constexpr auto CPP_fun(operator())(C && pred)(const //
                                                          requires(!range<C>))
            {
                return make_view_closure(
                    bind_back(unique_base_fn{}, static_cast<C &&>(pred)));
            }
        };

        /// \relates unique_fn
        /// \ingroup group-views
        RANGES_INLINE_VARIABLE(view_closure<unique_fn>, unique)
    } // namespace views
    /// @}
} // namespace ranges

#include <range/v3/detail/reenable_warnings.hpp>

#endif
