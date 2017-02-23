#pragma once

namespace MsiUtility
{
/**
 * @brief gets a property in a session
 *
 * @param aSession handle to the session
 *
 * @param aPropertyName the name of the property
 */
wstring GetProperty(MSIHANDLE aSession, const wstring & aPropertyName);

/**
 * @brief sets a property with a value
 *
 * @param aSession a handle to the session
 *
 * @param aPropertyName the name of the property
 *
 * @param aPropertyValue the value of the property
 */
void SetProperty(MSIHANDLE aSession, const wstring & aPropertyName, const wstring & aPropertyValue);

wstring FormatString(MSIHANDLE aDatabaseHandle, wstring aRecord);
};
