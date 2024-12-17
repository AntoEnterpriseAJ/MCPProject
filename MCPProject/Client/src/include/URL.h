#pragma once
#include <vector>
#include <algorithm>
#include <ranges>
#include <sstream>

class URL
{
public:
    URL(std::string_view baseURL) : m_baseURL{baseURL} {};

    template<typename... Args>
    URL& addToPath(Args&&... args)
    {
        (addPathPart(std::forward<Args>(args)), ...);
        return *this;
    }

    std::string build()
    {
        std::stringstream url;
        url << m_baseURL;
        std::ranges::for_each(m_parts, [this, &url](const auto& part){
            url << "/" << part;
        });

        m_parts.clear();
        return url.str();
    }

private:
    template <typename T>
    void addPathPart(T&& part)
    {
        m_parts.emplace_back(std::forward<T>(part));
    }
private:
    std::vector<std::string> m_parts;
    std::string              m_baseURL;
};