SKSEPluginVersion = []() noexcept {
	SKSE::PluginVersionData v{};
	v.PluginVersion({1, 0, 0});
	v.PluginName("AESkyrimPlugin");
	v.AuthorName("Thgewe");
	v.UsesAddressLibrary();
	v.UsesUpdatedStructs();
	v.CompatibleVersions({SKSE::RUNTIME_SSE_LATEST});
	return v;
}();

SKSEPluginLoad(const SKSE::LoadInterface *skse) {
	SKSE::Init(skse);
	logger::info("loaded!");
	return true;
}