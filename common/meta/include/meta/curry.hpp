
#pragma once


namespace meta{


template<typename Func, typename T>
struct lcurry;


template<template<typename ...> typename Func, typename... Ts, typename T>
struct lcurry<Func<curry::arg, Ts...>, T>{
  using type = 
};

}
