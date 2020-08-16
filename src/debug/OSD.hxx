/**
 * \file
 * \date November 2, 2019
 * \author Zermingore
 * \brief OSD templates implementation
 */

#ifndef OSD_HXX_
# define OSD_HXX_

# include <debug/OSD.hh>



namespace debug {


template<typename T>
void OSD::addPod(const T& value, const std::string& description)
{
  static_assert(std::is_trivial<T>::value,
                "OSD::addPod supports only Plain Old Data");

  std::string desc;
  if (description != "")
  {
    desc = description + ": ";
  }

  addText(desc + std::to_string(value));
}


} // namespace debug


#endif // OSD_HXX_
