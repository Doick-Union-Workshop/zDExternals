namespace GOTHIC_NAMESPACE
{
	static zSTRING Str_Upper(const zSTRING& t_str)
	{
		zSTRING str = t_str;
		return str.Upper();
	}

	static zSTRING Str_Lower(const zSTRING& t_str)
	{
		zSTRING str = t_str;
		return str.Lower();
	}

	static zSTRING Str_Capitel(const zSTRING& t_str)
	{
		zSTRING str = t_str;
		return str.UpperFirstLowerRest();
	}
}