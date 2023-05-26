#ifndef ASHITA_GBINDER_HPP_INCLUDED
#define ASHITA_GBINDER_HPP_INCLUDED

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/**
 * Main Ashita SDK Include
 * 
 * In order to compile a proper Ashita plugin, this header is required to be included. This header
 * includes the various other generally used parts of the Ashita SDK, as well as defines the various
 * SDK interfaces, enumerations, and other type definitions required.
 * 
 * To help with uniformed pathing, Ashita bases all SDK includes from a parent path. You can set this
 * parent path via the following environment variable on your system: 
 * 
 * ASHITA4_SDK_PATH
 */
#include "Ashita.h"
#include "../GkeySDK/Include/LogitechGkeyLib.h"

/**
 * GBinder Class Implementation
 * 
 * This is the main class object the plugin will create an instance of and return to Ashita when
 * the 'CreatePlugin' export is called. This class MUST inherit from the 'IPlugin' interface to
 * work properly with Ashita.
 */

class GBinder final : public IPlugin
{
    IAshitaCore* m_AshitaCore;          // The pointer to the main AshitaCore object.
    ILogManager* m_LogManager;          // The pointer to the main Ashita LogManager object.
    uint32_t m_PluginId;                // The plugins id. (The plugins current base address.)

    logiGkeyCBContext m_GKeyContext;

public:
    GBinder(void);
    ~GBinder(void) override;

    // Properties (Plugin Information)
    const char* GetName(void) const override;
    const char* GetAuthor(void) const override;
    const char* GetDescription(void) const override;
    const char* GetLink(void) const override;
    double GetVersion(void) const override;
    double GetInterfaceVersion(void) const override;
    int32_t GetPriority(void) const override;
    uint32_t GetFlags(void) const override;

    // Methods
    bool Initialize(IAshitaCore* core, ILogManager* logger, uint32_t id) override;
    void Release(void) override;
};

#endif // ASHITA_GBINDER_HPP_INCLUDED