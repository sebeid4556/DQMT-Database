#pragma once

#include"framework/common.h"

class Resource
{
    public:
        Resource(const std::filesystem::path& path);
        ~Resource();                
        std::string getFilename() const;
        std::string getFullPath() const;
    protected:
        virtual void load();            
        const std::string filename;
        const std::string full_path;
};

class ResourceImage : public Resource
{
    public:
        ResourceImage(const std::filesystem::path& path);
        ~ResourceImage();        
        SDL_Surface *getCopySurface();
        SDL_Texture *getCopyTexture();
    private:
        SDL_Surface *pSurface;

        void load() override;
};

class ResourceFont : public Resource
{
    public:
        ResourceFont(const std::filesystem::path& path);
        ~ResourceFont();        
        TTF_Font *getTTF();
    private:
        TTF_Font *pFont;

        void load() override;
};

class ResourceManager   //singleton
{
    public:                
        static ResourceManager* getInstance();
        void addDirectory(const std::string path);
        ResourceImage *getImage(const std::string& filename);
        ResourceFont *getFont(const std::string& filename);
    private:
        std::map<std::string, ResourceImage *> mResourceImages;
        std::map<std::string, ResourceFont *> mResourceFonts;

        static ResourceManager *s_pInstance;

        ResourceManager();        
        ResourceManager(const ResourceManager&) = delete;
        ResourceManager& operator=(const ResourceManager&) = delete;
        void addResource(ResourceImage *pRscImage);
        void addResource(ResourceFont *pRscFont);        
        virtual ~ResourceManager();                
};