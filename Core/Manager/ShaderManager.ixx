export module Misaka.Core.Manager.ShaderManager;

import <string>;
import <unordered_map>;
import <memory>;
import Misaka.Core.Renderer.Shader;
import Misaka.Core.CoreConfig;

namespace Misaka::Core::Manager {

export class ShaderManager {
public:
    void LoadShader(const std::string& name) {
        std::string vsPath = (CoreConfig::ShaderRoot / "bgfx" / "compiled" / ("vs_" + name + ".bin")).string();
        std::string fsPath = (CoreConfig::ShaderRoot / "bgfx" / "compiled" / ("fs_" + name + ".bin")).string();

        m_Shaders[name] = Renderer::Shader::Create(vsPath.c_str(), fsPath.c_str());
    }

    std::shared_ptr<Renderer::Shader> GetShader(const std::string& name) {
        return m_Shaders[name];
    }

private:
    std::unordered_map<std::string, std::shared_ptr<Renderer::Shader>> m_Shaders;
};

} // namespace Misaka::Core::Manager