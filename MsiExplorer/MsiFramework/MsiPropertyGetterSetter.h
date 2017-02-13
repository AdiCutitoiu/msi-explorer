#pragma once

namespace MsiPropertyGetterSetter
{
  /**
   * @brief gets a property in a session
   *
   * @param aSession handle to the session
   *
   * @param aPropertyName the name of the property
   */
  wstring Get(MSIHANDLE aSession, const wstring & aPropertyName);

  /**
   * @brief sets a property with a value
   *
   * @param aSession a handle to the session
   *
   * @param aPropertyName the name of the property
   *
   * @param aPropertyValue the value of the property
   */
  void Set(MSIHANDLE       aSession,
                  const wstring & aPropertyName,
                  const wstring & aPropertyValue);
};