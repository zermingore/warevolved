/**
 * \file
 * \brief OSD templates implementation
 * \author Zermingore
 * \date November 2, 2019
 */

#include <debug/OSD.hh>



namespace debug {


template<typename T>
void OSD::addPod(const T& value, const std::string description)
{
  static_assert(std::is_pod<T>::value,
                "OSD::addPod supports only Plain Old Data");

  std::string desc;
  if (description != "")
  {
    desc = description + ": ";
  }

  addText(desc + std::to_string(value));
}


} // namespace debug
