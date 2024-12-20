#ifndef LIST_UTILS_HPP
#define LIST_UTILS_HPP

#include <stdexcept>

template <typename T, typename List>
class ListUtils {
public:
    // конкатенира list2 към list1
    // O(n) по време и по O(n) по памет
    static void append(List& list1, List const& list2) {
        for(T const& x : list2)
            list1.insertLast(x);
    }

    // обръща реда на елементите в l
    // O(n) по време и O(1) по памет
    // TODO: да се направи конкретна реализация директно с представянето
    static void reverse(List& l) {
        typename List::Iterator it = l.begin();
        if (it.valid())
            while (it.next().valid()) {
                T x;
                l.deleteAfter(x, it);
                l.insertFirst(x);
            }
    }

    // разделя елементите на list в list1 и list2 така, че да са с приблизително
    // равна дължина
    // O(n) по време и по памет
    // TODO: да се направи реализация, която е O(1) по допълнителна памет
    // TODO: да се направи конкретна реализация, директно с представянето 
    static void split(List const& list, List& list1, List& list2) {
        if (!list1.empty() || !list2.empty())
            throw std::invalid_argument("Списъците list1 и list2 трябва да са празни!");
        List *me = &list1, *you = &list2;
        for(T const& x : list) {
            me->insertLast(x);
            std::swap(me, you);
        }
    }

    // слива два сортирани във възходящ ред списъка
    // O(n) по време и по памет
    // TODO: да се направи реализация, която е O(1) по памет, с преместване вместо копиране
    static List merge(List const& list1, List const& list2) {
        typename List::Iterator it1 = list1.begin(), it2 = list2.begin();
        List result;
        while (it1 && it2)
            if (*it1 < *it2)
                result.insertLast(*it1++);
            else
                result.insertLast(*it2++);
        // !it1 || !it2
        while(it1)
            result.insertLast(*it1++);
        while(it2)
            result.insertLast(*it2++);
       return result;
    }

    // сортира списъка сливайки сортираните му части
    // O(n log(n)) по време и O(n) по памет
    // TODO: да се реализира с O(1) по памет
    static List mergeSort(List const& list) {
        if (list.empty() || !list.begin().next().valid())
            // списък с 0 или 1 елемента
            return list;
        // 1. разделяме списъка на две
        List list1, list2;
        split(list, list1, list2);
        // 2. сортираме рекурсивно двата списъка
        // 3. сливаме двата сортирани списъка
        return merge(mergeSort(list1), mergeSort(list2));
    }
};

 
#endif // LIST_UTILS_HPP