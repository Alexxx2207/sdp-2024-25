#ifndef LIST_HIGH_ORDER_HPP
#define LIST_HIGH_ORDER_HPP



template <typename T, template <typename> class List, typename R = T>
class ListHighOrderFunctions {
public:

    using BinaryFunctionRight = R (*)(T, R);
    using BinaryFunctionLeft  = R (*)(R, T);
    using UnaryFunction = R (*)(T);
    using Predicate = bool (*)(T);

    using I = typename List<T>::Iterator;

    static R foldr(BinaryFunctionRight op, R nv, I it) {
        if (!it)
            return nv;
        return op(*it, foldr(op, nv, it.next()));
    }

    static R foldl(BinaryFunctionLeft op, R nv, I it) {
        R result = nv;
        while (it)
            result = op(result, *it++);
        return result;
    }

    static List<R> map(UnaryFunction f, I it) {
        List<R> result;
        while (it)
            result.insertLast(f(*it++));
        return result;
    }

    static List<T> filter(Predicate p, I it) {
        List<T> result;
        for( ; it ; ++it)
            if (p(*it))
                result.insertLast(*it);
        return result;
    }

    // TODO: мутираща версия на map
    // TODO: мутираща версия на filter
    
};

#endif // LIST_HIGH_ORDER_HPP