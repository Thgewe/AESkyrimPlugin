class ActivateSink : public RE::BSTEventSink<RE::TESActivateEvent>
{
public:
	static ActivateSink* GetSingleton()
	{
		static ActivateSink instance;
		return &instance;
	}

	RE::BSEventNotifyControl ProcessEvent(
		const RE::TESActivateEvent*               a_event,
		RE::BSTEventSource<RE::TESActivateEvent>* a_eventSource) override
	{

		if (a_event && a_event->objectActivated && a_event->actionRef)
		{
			logger::info("{} activated {}",
				a_event->actionRef->GetDisplayFullName(), a_event->objectActivated->GetDisplayFullName());
		}

		return RE::BSEventNotifyControl::kContinue;
	};

private:
	ActivateSink() = default;
	~ActivateSink() override = default;
	ActivateSink(const ActivateSink&) = delete;
	ActivateSink& operator=(const ActivateSink&) = delete;
};

SKSEPluginVersion = []() noexcept {
	SKSE::PluginVersionData v{};
	v.PluginVersion({ 1, 0, 0 });
	v.PluginName("AESkyrimPlugin");
	v.AuthorName("Thgewe");
	v.UsesAddressLibrary();
	v.UsesUpdatedStructs();
	v.CompatibleVersions({ SKSE::RUNTIME_SSE_LATEST });
	return v;
}();

SKSEPluginLoad(const SKSE::LoadInterface* skse)
{
	SKSE::Init(skse);
	logger::info("loaded!");

	SKSE::GetMessagingInterface()->RegisterListener([](SKSE::MessagingInterface::Message* msg){
		if (msg && msg->type == SKSE::MessagingInterface::kDataLoaded) {
			RE::ScriptEventSourceHolder::GetSingleton()->AddEventSink<RE::TESActivateEvent>(ActivateSink::GetSingleton());
			logger::info("Activate sink registered");
		}
	});

	return true;
}
