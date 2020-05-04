#pragma once
#include "../Header/Header.h"

namespace fops
{
	#if defined __has_include && __has_include ("QFileDialog")
	namespace reg
	{
		static void open_path_file(QSettings& settings, const QString& param)
		{
			QString file_path{ QFileDialog::getOpenFileName(0, "Открыть", settings.value(param).toString()) };
			if (file_path.isEmpty())
			{
				return;
			}
			settings.setValue(param, file_path);
			return;
		}
		static void save_path_file(QSettings& settings, const QString& param)
		{
			QString file_path{ QFileDialog::getSaveFileName(0, "Сохранить", settings.value(param).toString()) };
			if (file_path.isEmpty())
			{
				return;
			}
			settings.setValue(param, file_path);
			return;
		}
		static void select_path_dir(QSettings& settings, const QString& param)
		{
			QString file_path{ QFileDialog::getExistingDirectory(0, "Выбрать", settings.value(param).toString()) };
			if (file_path.isEmpty())
			{
				return;
			}
			settings.setValue(param, file_path);
			return;
		}
	}
	#endif
	#if defined __has_include && __has_include ("QLineEdit")
	namespace edit
	{
		static void insert_path_dir(QLineEdit* edit, QSettings& settings, const QString& param)
		{
			QString file_path{ QFileDialog::getExistingDirectory(0, "", settings.value(param).toString()) };
			if (file_path.isEmpty())
			{
				return;
			}
			edit->setText(file_path);
			return;
		}
		static void insert_path_file(QLineEdit* edit, QSettings& settings, const QString& param)
		{
			QString file_path{ QFileDialog::getOpenFileName(0, "", settings.value(param).toString()) };
			if (file_path.isEmpty())
			{
				return;
			}
			edit->setText(file_path);
			return;
		}
	}
	#endif
	//static auto ReadFile = [](const auto& path) {
	//	std::ifstream src(path, std::ios::binary);
	//	std::vector<char> buf(static_cast<int>(fs::file_size(path)));
	//	src.read(buf.data(), buf.size());
	//	std::vector<double> out(buf.size());
	//	std::transform(
	//		std::execution::par,
	//		std::cbegin(buf), std::cend(buf),
	//		std::begin(out),
	//		[](const char& elm) {
	//			return static_cast<double>(elm) / static_cast<double>(255);
	//		}
	//	);
	//	return out;
	//};
	//static auto read_file(const fs::directory_entry& entry) {
	//	std::ifstream src(entry.path(), std::ios::binary);
	//	std::vector<char> buf(static_cast<int>(fs::file_size(entry.path())));
	//	src.read(buf.data(), buf.size());
	//	std::vector<double> out(buf.size());
	//	std::transform(
	//		std::execution::par,
	//		std::cbegin(buf), std::cend(buf),
	//		std::begin(out),
	//		[](const char& elm) {
	//			return static_cast<double>(elm) / static_cast<double>(255);
	//		}
	//	);
	//	return out;
	//};

	//static auto is_contains = [](const auto& entry, const auto& str) {
	//	auto name = entry.path();
	//	return (
	//		std::search(
	//			std::begin(name), std::end(name),
	//			std::begin(str), std::end(str)) != std::end(name));
	//};
	//template<typename... Args>
	//constexpr static auto is_filename_contains(Args&&... args) {
	//	std::list<std::string> lst;
	//	(lst.push_back(std::forward<Args>(args)), ...);
	//	return[lst{ std::move(lst) }](const auto& entry) {
	//		for (const auto& str : lst) {
	//			bool is_found{ is_filename_contains(str)(entry) ? true : false };
	//			if (is_found) {
	//				return true;
	//			}
	//		}
	//		return false;
	//	};
	//}
	//constexpr auto is_filename_contains(const std::string& str) {
	//	return [&](const auto& entry) constexpr {
	//		auto name{ entry.path().filename().generic_string() };
	//		return
	//			std::search(
	//				std::begin(name), std::end(name),
	//				std::begin(str), std::end(str)) != std::end(name);
	//	};
	//}
	//template<typename... Args>
	//constexpr static auto is_not_filename_contains(Args&&... args) {
	//	std::list<std::string> lst;
	//	(lst.push_back(std::forward<Args>(args)), ...);
	//	return[lst{ std::move(lst) }](const auto& entry)constexpr {
	//		for (const auto& str : lst) {
	//			bool is_not_found{ is_not_filename_contains(str)(entry) ? true : false };
	//			if (!is_not_found) {
	//				return false;
	//			}
	//		}
	//		return true;
	//	};
	//}
	//constexpr auto is_not_filename_contains(const std::string& str) {
	//	return [&](const auto& entry) constexpr {
	//		auto name{ entry.path().filename().generic_string() };
	//		return std::search(
	//			std::begin(name), std::end(name),
	//			std::begin(str), std::end(str)) == std::end(name);
	//	};
	//}
	template<typename T, typename Exe>
	constexpr bool find(T&& c, T&& s, Exe exe)
	{
		return std::search(
			exe,
			std::begin(std::forward<T>(c)), std::end(std::forward<T>(c)),
			std::begin(std::forward<T>(s)), std::end(std::forward<T>(s))
		) != std::end(c) ? true : false;
	}

	constexpr auto is_file = [](const auto& entry)
	{
		return entry.is_regular_file();
	};

	static bool is_not_file(const fs::directory_entry& entry)
	{
		return !entry.is_regular_file();
	};

	//static bool is_equally_size(const fs::path& dir) {
	//	uint64_t old{ 0 };
	//	for (const auto& size : fs::directory_iterator{ dir }
	//		| ranges::views::remove_if(is_not_file)
	//		| ranges::views::transform([](const auto& entry) {return entry.file_size(); })) {

	//		bool state = old == 0 ? old = size : size != old ? false : true;
	//		if (!state) {
	//			return false;
	//		}
	//	}
	//	return true;
	//}

	///*template<template<typename>typename C, typename T>
	//static  auto read_all_file(const fs::path& dir, const std::string& suffix) {
	//	C<C<T>> out;
	//	for (const auto& pair : fs::directory_iterator{ dir }
	//		| ranges::views::remove_if(is_not_file)
	//		| ranges::views::remove_if(is_not_filename_contains(suffix))
	//		| ranges::views::transform(
	//			[](const auto& entry) {
	//				return
	//					std::pair(
	//						fop::ReadFile(entry.path()),
	//						std::vector<double>{fop::is_filename_contains(std::string{ "true" })(entry) ? 1.0 : 0.0});
	//			})) {
	//		out.push_back(pair.first);
	//	}
	//	return out;
	//}*/
	//template<typename T>
	//constexpr static std::unordered_map<T, T> Types{
	//	{ 1, 255 },
	//	{ 2, 65535 },
	//	{ 3, 4294967295 },
	//	{ 4, -1 }
	//}
	//	static decltype(auto) rationing(const char& elm) {
	//	return elm / 255;
	//}
	//static decltype(auto) data_rationing(const std::vector<char>& data) {
	//	return ranges::actions::transform(rationing);
	//};
	constexpr auto read_file = [](const fs::directory_entry& entry)
	{
		fs::path file{ entry.path() };
		std::ifstream src(file, std::ios::binary);
		std::vector<char> out(static_cast<int>(fs::file_size(file)));
		src.read(out.data(), out.size());
		return out;
	};
	////template<template<typename>typename C, typename T, typename... Args>
	////static  decltype(auto) read_all_files(fs::path&& dir, Args&&... args) {
	////	//C<C<T>> out;
	////	std::vector<std::vector<double>> in;
	////	for (
	////		const auto& pair : fs::directory_iterator{ dir }
	////		| ranges::views::remove_if(fop::is_not_file)
	////		| ranges::views::remove_if(
	////			fop::is_not_filename_contains(
	////				std::string{ "true" }, std::string{ "false" }))
	////		| ranges::views::transform(
	////			[](const auto& entry) {
	////				return
	////					std::pair(
	////						fop::read_file(entry),
	////						std::vector<double>{fop::is_filename_contains(std::string{ "true" })(entry) ? 1.0 : 0.0}); })
	////		)
	////	{
	////		in.emplace_back(pair.second);
	////	}
	////	return in;
	////};
}

TEST(CheckIsTrue, Find)
{
	fs::path dir{ fs::current_path() };
	for (const auto& entry : fs::directory_iterator{ dir }
		 | views::remove_if(fops::is_not_file)
		 )
	{
		//ASSERT_EQ(entry.is_regular_file(), false);
	}
}