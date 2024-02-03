#include <iostream>
#include <string>
#include <utility>

namespace detail
{
    template<size_t N, typename... Types>
    struct nth_type;

    // Partial specialization that "peels off" types from the pack until N is 0
    template<size_t N, typename T, typename... Rest>
    struct nth_type<N, T, Rest...> : nth_type<N - 1, Rest...> {};

    // Base case specialization when N is 0, captures the current type T
    template<typename T, typename... Rest>
    struct nth_type<0, T, Rest...> {
        using type = T;
    };

    // Helper template to simplify usage of nth_type
    template<size_t N, typename... Types>
    using nth_type_t = typename nth_type<N, Types...>::type;
}


template<typename... Nodes>
struct pipeline: Nodes...
{
    using Nodes::process...;

    template<size_t id> auto& get()
    {
        using Node = detail::nth_type_t<id, Nodes...>;
        return static_cast<Node&>(*this);
    }
};


namespace detail
{
    template<typename Traits, template<typename, size_t> class... Nodes, size_t... I>
    auto make_pipeline(std::index_sequence<I...>) -> pipeline<Nodes<Traits, I>...>;
}

template<typename Traits, template<typename, size_t> class... Nodes>
struct pipeline_engine
{
    using pipeline = decltype(detail::make_pipeline<Traits, Nodes...>(std::make_index_sequence<sizeof...(Nodes)>{}));
};


/*
namespace detail {
    template<typename Traits, template<typename, size_t> class... Nodes>
    struct indexed_pipeline_maker;
    
    template<typename Traits, template<typename, size_t> class... Nodes, size_t... I>
    struct indexed_pipeline_maker<Traits, Nodes..., std::index_sequence<I...>> {
        using type = pipeline<Nodes<Traits, I>...>;
    };
}

template<typename Traits, template<typename, size_t> class... Nodes>
struct pipeline_engine {
    using pipeline = typename detail::indexed_pipeline_maker<Traits, Nodes..., std::make_index_sequence<sizeof...(Nodes)>>::type;
};
*/

template<typename Traits, size_t I>
struct node
{
    using pipeline_engine = pipeline_engine<Traits>;

    void process(std::string msg)
    {
        //auto thiz = static_cast<typename pipeline_engine::pipeline&>(*this);
        //static_assert(std::is_same<decltype(*this), decltype(thiz)>::value, "Should be the same type");
        std::cout << "Process : " << msg << std::endl;      
    }
};

struct traits {};

int main()
{
    pipeline_engine<traits, node>::pipeline p;
    p.process("hello");
}