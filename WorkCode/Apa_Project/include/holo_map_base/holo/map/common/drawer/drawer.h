/*!
 * \brief Drawer
 * \author Yuchao Hu (huyuchao@holomatic.com)
 * \date 2018-03-15
 * \attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 * \attention Refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#ifndef HOLO_MAP_FEATURE_DRAWER_DRAWER_H_
#define HOLO_MAP_FEATURE_DRAWER_DRAWER_H_

#include <functional>
#include <map>
#include <memory>
#include <mutex>
#include <set>
#include <string>
#include <thread>

#include <holo/os/tictoc_timer.h>
#include <holo/geometry/point2.h>

#include <holo/map/common/common_type_define.h>

namespace holo
{
namespace map
{
///
/// API for Drawer
///
class Drawer
{
public:
    struct Color
    {
        Color(const uint8_t _b, const uint8_t _g, const uint8_t _r) : b(_b), g(_g), r(_r)
        {
        }
        uint8_t b;
        uint8_t g;
        uint8_t r;
    };

public:
    // disable copy and move
    Drawer(const Drawer&) = delete;
    Drawer(Drawer&&) = delete;
    Drawer& operator=(const Drawer&) = delete;
    Drawer& operator=(Drawer&&) = delete;

    ///
    /// @brief Instance of this singleton
    ///
    /// @return Reference of this singleton's instance
    ///
    static Drawer& Instance();

    ///
    /// @brief Close thread of this singleton
    ///
    /// @return Nothing
    ///
    void Close();

    ///
    /// @brief Create figure
    ///
    /// @param [in] _name Figure name
    /// @param [in] _width Figure width, pixel
    /// @param [in] _height Figure height, pixel
    /// @reutrn Nothing
    ///
    void CreateFigure(const ::std::string& _name, const Size _width, const Size _height);

    ///
    /// @brief Clear figure
    ///
    /// @param [in] _name Figure name
    /// @return Nothing
    ///
    void ClearFigure(const ::std::string& _name);

    ///
    /// @brief Draw circle
    ///
    /// @param [in] _name Figure name
    /// @param [in] _center Circle center, pixel
    /// @param [in] _radius Circle radius, pixel
    /// @param [in] _color Circle color
    /// @param [in] _thickness Circle thickness, pixel
    /// @return Nothing
    ///
    void DrawCircle(const ::std::string& _name, const geometry::Point2T<float64_t>& _center, const int _radius,
                    const Color& _color,
                    const int _thickness = 1);

    ///
    /// @brief Draw line
    ///
    /// @param [in] _name Figure name
    /// @param [in] _first_point First point of line, pixel
    /// @param [in] _second_point Second point of line, pixel
    /// @param [in] _color Line color
    /// @param [in] _thickness Line thickness, pixel
    /// @return Nothing
    ///
    void DrawLine(const ::std::string& _name, const geometry::Point2T<float64_t>& _first_point,
                  const geometry::Point2T<float64_t>& _second_point,
                  const Color& _color, const int _thickness = 1);

    ///
    /// @brief Draw lines
    ///
    /// @param[in] _name Figure name
    /// @param[in] _points Points, pixel
    /// @param[in] _color Line color
    /// @param[in] _thickness Line thickness, pixel
    /// @return Nothing
    ///
    void DrawLines(const ::std::string& _name, const ::std::vector<geometry::Point2T<float64_t>>& _points,
                   const Color& _color,
                   const int _thickness = 1);

    ///
    /// @brief Show figure
    ///
    /// @param [in] _name Figure name
    /// @return Nothing
    ///
    void ShowFigure(const ::std::string& _name);

    ///
    /// @brief Hide figure
    ///
    /// @param[in] _name Figure name
    /// @return Nothing
    ///
    void HideFigure(const ::std::string& _name);

private:
    Drawer();
    virtual ~Drawer();

    void Start();
    void Stop();
    void Loop();

private:
    ::std::map<std::string, ::std::shared_ptr<void>> map_ptr_mat_;

    ::std::set<::std::string> set_mat_to_show_;
    ::std::set<::std::string> set_mat_to_hide_;
    ::std::set<::std::string> set_window_to_create_;

    TicTocTimer timer_;
    ::std::function<void(void)> thread_function_;
    ::std::shared_ptr<::std::thread> ptr_thread_;
    bool keep_running_;
    float64_t threshold_loop_sleep_;

    ::std::mutex mutex_map_ptr_mat_;
    ::std::mutex mutex_set_mat_to_show_;
    ::std::mutex mutex_set_mat_to_hide_;
    ::std::mutex mutex_set_window_to_create_;
};  // class Drawer
}  // namespace map
}  // namespace holo
#endif  //  HOLO_MAP_FEATURE_DRAWER_DRAWER_H_
