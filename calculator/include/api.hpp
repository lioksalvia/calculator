#ifndef CALCULATOR_API_HPP_
#define CALCULATOR_API_HPP_

#ifdef _WIN32
#ifdef CALCULATOR_EXPORTS
#define CALCULATOR_API __declspec(dllexport)
#else
#define CALCULATOR_API __declspec(dllimport)
#endif
#else
#define CALCULATOR_API
#endif

#endif  // !CALCULATOR_API_HPP_