#pragma once
#include "MsInstallerRecord.h"

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

/**
 * @param aSession handle to install
 *
 * @param the record to be formatted
 *
 * @param aFieldNumber the field to be formatted
 */
wstring FormatField(MSIHANDLE aSession, const MsInstallerRecord & aRecord, int aFieldNumber);
};
