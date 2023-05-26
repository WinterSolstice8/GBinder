#include "GBinderPlugin.hpp"
#include "../GkeySDK/Include/LogitechGkeyLib.h"
#include <format>

/**
 * Constructor and Deconstructor
 */
GBinder::GBinder(void)
    : m_AshitaCore{nullptr}
    , m_LogManager{nullptr}
    , m_PluginId{0}
    , m_GKeyContext{}
{}
GBinder::~GBinder(void)
{}

/**
 * Returns the plugins name.
 *
 * @return {const char*} The plugins name.
 */
const char* GBinder::GetName(void) const
{
    return "GBinder";
}

/**
 * Returns the plugins author.
 *
 * @return {const char*} The plugins author.
 */
const char* GBinder::GetAuthor(void) const
{
    return "WinterSolstice8";
}

/**
 * Returns the plugins description.
 *
 * @return {const char*} The plugins description.
 */
const char* GBinder::GetDescription(void) const
{
    return "GBinder implements Logitech G Keys";
}

/**
 * Returns the plugins homepage link.
 *
 * @return {const char*} The plugins homepage link.
 */
const char* GBinder::GetLink(void) const
{
    return "";
}

/**
 * Returns the plugins version.
 *
 * @return {double} The plugins version.
 */
double GBinder::GetVersion(void) const
{
    return 1.0f;
}

/**
 * Returns the plugins Ashita SDK interface version it was compiled against.
 *
 * @return {double} The plugins interface version.
 */
double GBinder::GetInterfaceVersion(void) const
{
    return ASHITA_INTERFACE_VERSION;
}

/**
 * Returns the plugins execution priority.
 *
 * @return {int32_t} The plugins execution priority.
 * @notes
 *
 *      The priority value is used to determine the execution order of the plugins loaded in Ashita. When an event is fired, Ashita
 *      will loop through each of the loaded plugins and allow them to attempt to handle the event. The order that the plugins are
 *      passed the event is determined by this priority. By default, 0 will load a plugin 'next' in the list of plugins who also are
 *      set to 0. Meaning if other plugins are already loaded at 0, and your plugin is also 0 your plugin will be last.
 *      
 *      Plugins can force themselves sooner or later into the execution order by using this value (both negative and position).
 *      Negative values will place your plugin sooner in the execution order, while positive values will place it later.
 *      
 *      Plugins should use 0 by default if order does not matter to their purpose.
 */
int32_t GBinder::GetPriority(void) const
{
    return 0;
}

/**
 * Returns the plugins flags.
 *
 * @return {uint32_t} The plugins flags.
 * @notes
 * 
 *      Ashita offers a various number of events that can be invoked inside of a plugin, allowing plugins to have a lot of control
 *      over the flow of the game. However, this can create a lot of overhead, more specifically on lower end machines. Plugins can
 *      use this property to specify the exact events it plans to make use of, allowing Ashita to only invoke ones it needs.
 *      
 *      Plugins should explicitly state which flags they plan to make use of and avoid using 'All' flags.
 *      This can help with the performance of the game for lower end machines.
 *      
 *      See the 'Ashita::PluginFlags' enumeration for more information on what each flag does.
 */
uint32_t GBinder::GetFlags(void) const
{
    return (uint32_t)Ashita::PluginFlags::None;
}

/**
 * Event invoked when the plugin is being loaded and initialized.
 *
 * @param {IAshitaCore*} core - The main Ashita core instance used to interact with the Ashita hook.
 * @param {ILogManager*} logger - The log manager instance used to write to the debug log files.
 * @param {uint32_t} id - The plugins unique id. (Matches the plugins module base address.)
 * @return {bool} True on success, false otherwise.
 *
 * @notes
 * 
 *      Plugins must return true from this function in order to be considered valid and continue to load.
 *      If your plugin fails to meet any requirements you feel are manditory for it to run, you should return false here and prevent it
 *      from loading further.
 */
bool GBinder::Initialize(IAshitaCore* core, ILogManager* logger, const uint32_t id)
{
    // Store the incoming parameters for later use..
    this->m_AshitaCore = core;
    this->m_LogManager = logger;
    this->m_PluginId   = id;

    m_GKeyContext.gkeyContext  = this;
    m_GKeyContext.gkeyCallBack = (logiGkeyCB)[](GkeyCode gkeyCode, const wchar_t* gkeyOrButtonString, void* context)
    {
        UNREFERENCED_PARAMETER(gkeyOrButtonString);
        if (gkeyCode.keyDown)
        {
            char alias[32]  = {};
            
            if (gkeyCode.mouse)
            {
                // Doesn't appear to work?
                // send command like "/mouse_m1g1"
                snprintf(alias, sizeof(alias), "/mouse_m%ug%u", gkeyCode.mState, gkeyCode.keyIdx);
            }
            else
            {
                // send command like "/m1g1"
                snprintf(alias, sizeof(alias), "/m%ug%u", gkeyCode.mState, gkeyCode.keyIdx);
            }

            static_cast<GBinder*>(context)->m_AshitaCore->GetChatManager()->QueueCommand(1, alias);
        }
    };

    LogiGkeyInit(&m_GKeyContext);
    return true;
}

/**
 * Event invoked when the plugin is being unloaded.
 *
 * @notes
 *
 *      Plugins should use this event to cleanup all resources they created or used during their lifespan.
 *      (ie. Fonts, primitives, textures, Direct3D related resources, memory allocations, etc.)
 */
void GBinder::Release(void)
{
    LogiGkeyShutdown();
}

/**
 * Returns an instance of this plugins main class.
 * 
 * @param {const char*} args - The arguments passed to the plugin when it was loaded.
 * @return {IPlugin*} The plugins class object instance.
 * @notes
 * 
 *      This export must be present for a plugin to load properly!
 *      
 *      The args parameter can be used to prepare the plugin in any special manner for specific properties based on the arguments passed.
 *      For example, if you wish to have a password required to load the plugin, this can be used for that kind of thing. (Not recommended
 *      as this is a weak form of authentication, just an example.)
 */
__declspec(dllexport) IPlugin* __stdcall expCreatePlugin(const char* args)
{
    UNREFERENCED_PARAMETER(args);

    return new GBinder();
}

/**
 * Returns the plugins Ashita interface version it was compiled against.
 * 
 * @return {double} The plugins interface version.
 * @notes
 * 
 *      This export must be present for a plugin to load properly!
 */
__declspec(dllexport) double __stdcall expGetInterfaceVersion(void)
{
    return ASHITA_INTERFACE_VERSION;
}