#ifndef CALCULATOR__API_HPP_
#define CALCULATOR__API_HPP_

#ifdef _WIN32
#ifdef CALCULATOR_EXPORTS
#define CALCULATOR_API __declspec(dllexport)
#else
#define CALCULATOR_API __declspec(dllimport)
#endif
#elif
#define CALCULATOR_API
#endif

#endif  // !CALCULATOR__API_HPP_