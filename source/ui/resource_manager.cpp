#include"resource_manager.h"
#include"framework/component/component.h"
#include"framework/bclim.h"
#include"../util/file.h"

//=====================================================================================================================
// Resource
//=====================================================================================================================

Resource::Resource(const std::filesystem::path& path) : full_path(path.string()), filename(path.filename().string())
{
    ;
}

Resource::~Resource(){}

std::string Resource::getFilename() const
{
    return filename;
}

std::string Resource::getFullPath() const
{
    return full_path;
}

void Resource::load(){}

//=====================================================================================================================
// ResourceImage
//=====================================================================================================================

ResourceImage::ResourceImage(const std::filesystem::path& path) : Resource(path)
{
    load();
}

ResourceImage::~ResourceImage()
{
    if(pSurface) SDL_FreeSurface(pSurface);
}

void ResourceImage::load()
{
    const std::string path = full_path;
    if(checkExtension(path, ".png"))
    {
        pSurface = IMG_Load(path.c_str());
        if(!pSurface)
        {
            fatalError(IMG_GetError(), "img2surface");
        }
    }
    else if(checkExtension(path, ".bclim"))
    {
        pSurface = loadBCLIMSurface(path.c_str());
    }
    else
    {
        LOG_ERROR("expected .png or .bclim");
        fatalError("unsupported file extention");
    }    
}

SDL_Surface *ResourceImage::getCopySurface()
{
    if(!pSurface) fatalError("attempting to copy NULL surface");
    SDL_Surface *pRet = SDL_DuplicateSurface(pSurface);    
    if(!pRet) fatalError(SDL_GetError());
    return pRet;
}

SDL_Texture *ResourceImage::getCopyTexture()
{
    SDL_Texture *pRet = SDL_CreateTextureFromSurface(UIComponent::getRenderer(), pSurface);
    if(!pRet) fatalError(SDL_GetError());
    return pRet;
}

//=====================================================================================================================
// ResourceFont
//=====================================================================================================================

ResourceFont::ResourceFont(const std::filesystem::path& path) : Resource(path)
{
    load();
}

ResourceFont::~ResourceFont()
{
    TTF_CloseFont(pFont);
}

void ResourceFont::load()
{
    pFont = TTF_OpenFont(full_path.c_str(), 1);
    if(!pFont)
    {
        fatalError(TTF_GetError(), "UImanager::laodFont");
    }
}

TTF_Font *ResourceFont::getTTF()
{
    if(!pFont) fatalError("pFont not initialized yet");
    return pFont;
}

//=====================================================================================================================
// ResourceManager
//=====================================================================================================================

ResourceManager *ResourceManager::s_pInstance = nullptr;

ResourceManager::ResourceManager()
{    
    addDirectory("../resource");
    addDirectory("../ROM/raw/romfs/data/MonsterIcon");
}

ResourceManager::~ResourceManager()
{
    for(auto const& pair : mResourceImages)
    {
        delete pair.second;
    }
}

ResourceManager *ResourceManager::getInstance()
{
    if(s_pInstance == nullptr)
    {
        s_pInstance = new ResourceManager();
    }
    return s_pInstance;
}

ResourceImage *ResourceManager::getImage(const std::string& filename)
{    
    auto it = mResourceImages.find(filename);
    if(it != mResourceImages.end())
    {
        return mResourceImages.at(filename);
    }
    else
    {
        LOG_ERROR(std::string("cannot find " + filename).c_str());
        fatalError("resource not found");
    }
    return NULL;    //never reaches here
}

ResourceFont *ResourceManager::getFont(const std::string& filename)
{    
    auto it = mResourceFonts.find(filename);
    if(it != mResourceFonts.end())
    {
        return mResourceFonts.at(filename);
    }
    else
    {
        LOG_ERROR(std::string("cannot find " + filename).c_str());
        fatalError("resource not found");
    }
    return NULL;    //never reaches here
}

void ResourceManager::addResource(ResourceImage *pRscImage)
{
    mResourceImages.insert(std::pair<std::string, ResourceImage *>(pRscImage->getFilename(), pRscImage));
}

void ResourceManager::addResource(ResourceFont *pRscFont)
{
    mResourceFonts.insert(std::pair<std::string, ResourceFont *>(pRscFont->getFilename(), pRscFont));
}

void ResourceManager::addDirectory(const std::string path)
{
    const std::filesystem::path root = path;    

    std::cout << "\n[+]ResourceManager: root: " << root << std::endl;

    for(const std::filesystem::directory_entry& entry : std::filesystem::recursive_directory_iterator(root))
    {
        if(!entry.is_regular_file()) continue;  //only get files  

        std::cout << "[ResourceManager] " << "Loading " << entry << std::endl;      
                
        const std::string extension = entry.path().string();

        if(checkExtension(extension, ".png") || checkExtension(extension, ".bclim"))
        {
            addResource(new ResourceImage(entry.path()));
        }
        else if(checkExtension(extension, ".ttf"))
        {
            addResource(new ResourceFont(entry.path()));
        }
        else
        {
            std::string error_msg = entry.path().string() + " is not supported";
            error(error_msg.c_str(), "ResourceManager::loadAllFrom");
        }
    }
}