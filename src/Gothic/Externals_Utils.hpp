namespace GOTHIC_NAMESPACE
{
    // by Boguœ
    template<typename T>
    int _cdecl GetArrayValue()
    {
        const auto par = zCParser::GetParser();

        int index;
        par->GetParameter(index);

        const auto statArray = reinterpret_cast<T*>(par->PopVarAddress());

        par->SetReturn(statArray[index]);

        return {};
    }

    // by Boguœ
    template<typename T>
    int _cdecl SetArrayValue()
    {
        const auto par = zCParser::GetParser();

        T value;
        par->GetParameter(value);

        int index;
        par->GetParameter(index);

        const auto statArray = reinterpret_cast<T*>(par->PopVarAddress());

        statArray[index] = static_cast<T&&>(value);

        return {};
    }

    static int Ext_RGBA(const int r, const int g, const int b, const int a)
    {
        const zCOLOR color
        {
            static_cast<unsigned char>(r),
            static_cast<unsigned char>(g),
            static_cast<unsigned char>(b),
            static_cast<unsigned char>(a)
        };

        return static_cast<int>(color.dword);
    }
}