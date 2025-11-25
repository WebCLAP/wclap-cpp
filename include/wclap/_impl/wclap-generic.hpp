
/* Generated code - do not edit by hand.

This includes all the CLAP API typedefs and structs, but:
	* renamed clap_ -> wclap_
	* T * replaced by Pointer<T>
	* function pointers replaced by Function<Return, Args...>

You should be able to include this inside another namespace, as long as Function<> and Pointer<> are defined.  These must be simple wrappers around integers, and have the same size as pointers inside the WASM module.
*/

struct wclap_version {
   uint32_t major;
   uint32_t minor;
   uint32_t revision;
};
struct wclap_plugin_entry {
   wclap_version_t wclap_version;
   Function<bool,Pointer<const char> plugin_path> init;
   Function<void,void> deinit;
   Function<Pointer<const void> ,Pointer<const char> factory_id> get_factory;
};
struct wclap_version {
   uint32_t major;
   uint32_t minor;
   uint32_t revision;
};
struct wclap_host {
   wclap_version_t wclap_version;

   Pointer<void> host_data;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> version;
   Function<Pointer<const void> ,Pointer<const struct wclap_host> host, Pointer<const char> extension_id> get_extension;
   Function<void,Pointer<const struct wclap_host> host> request_restart;
   Function<void,Pointer<const struct wclap_host> host> request_process;
   Function<void,Pointer<const struct wclap_host> host> request_callback;
};
typedef int64_t wclap_beattime;
typedef int64_t wclap_sectime;
typedef uint32_t wclap_id;
typedef int32_t wclap_note_expression;
struct wclap_event_header {
   uint32_t size;
   uint32_t time;
   uint16_t space_id;
   uint16_t type;
   uint32_t flags;
};
struct wclap_event_note {
   wclap_event_header_t header;

   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;
   double  velocity;
};
struct wclap_event_note_expression {
   wclap_event_header_t header;

   wclap_note_expression expression_id;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_value {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_mod {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double amount;
};
struct wclap_event_param_gesture {
   wclap_event_header_t header;
   wclap_id param_id;
};
struct wclap_event_transport {
   wclap_event_header_t header;

   uint32_t flags;

   wclap_beattime song_pos_beats;
   wclap_sectime  song_pos_seconds;

   double tempo;
   double tempo_inc;

   wclap_beattime loop_start_beats;
   wclap_beattime loop_end_beats;
   wclap_sectime  loop_start_seconds;
   wclap_sectime  loop_end_seconds;

   wclap_beattime bar_start;
   int32_t       bar_number;

   uint16_t tsig_num;
   uint16_t tsig_denom;
};
struct wclap_event_midi {
   wclap_event_header_t header;

   uint16_t port_index;
   uint8_t  data[3];
};
struct wclap_event_midi_sysex {
   wclap_event_header_t header;

   uint16_t       port_index;
   Pointer<const uint8_t> buffer;
   uint32_t       size;
};
struct wclap_event_midi2 {
   wclap_event_header_t header;

   uint16_t port_index;
   uint32_t data[4];
};
struct wclap_input_events {
   Pointer<void> ctx;
   Function<uint32_t,Pointer<const struct wclap_input_events> list> size;
   Function<Pointer<const wclap_event_header_t> ,Pointer<const struct wclap_input_events> list, uint32_t index> get;
};
struct wclap_output_events {
   Pointer<void> ctx;
   Function<bool,Pointer<const struct wclap_output_events> list,
                            Pointer<const wclap_event_header_t>       event> try_push;
};
struct wclap_audio_buffer {
   Pointer<Pointer<float>>  data32;
   Pointer<Pointer<double>> data64;
   uint32_t channel_count;
   uint32_t latency;
   uint64_t constant_mask;
};
typedef int32_t wclap_process_status;
struct wclap_process {
   int64_t steady_time;
   uint32_t frames_count;
   Pointer<const wclap_event_transport_t> transport;
   Pointer<const wclap_audio_buffer_t> audio_inputs;
   Pointer<wclap_audio_buffer_t>       audio_outputs;
   uint32_t                   audio_inputs_count;
   uint32_t                   audio_outputs_count;
   Pointer<const wclap_input_events_t>  in_events;
   Pointer<const wclap_output_events_t> out_events;
};
struct wclap_plugin_descriptor {
   wclap_version_t wclap_version;
   Pointer<const char> id;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> manual_url;
   Pointer<const char> support_url;
   Pointer<const char> version;
   Pointer<const char> description;
   Pointer<const char> Pointer<const> features;
};
struct wclap_plugin {
   Pointer<const wclap_plugin_descriptor_t> desc;

   Pointer<void> plugin_data;
   Function<bool,Pointer<const struct wclap_plugin> plugin> init;
   Function<void,Pointer<const struct wclap_plugin> plugin> destroy;
   Function<bool,Pointer<const struct wclap_plugin> plugin,
                            double                    sample_rate,
                            uint32_t                  min_frames_count,
                            uint32_t                  max_frames_count> activate;
   Function<void,Pointer<const struct wclap_plugin> plugin> deactivate;
   Function<bool,Pointer<const struct wclap_plugin> plugin> start_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> stop_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> reset;
   Function<wclap_process_status,Pointer<const struct wclap_plugin> plugin,
                                          Pointer<const wclap_process_t>     process> process;
   Function<Pointer<const void> ,Pointer<const struct wclap_plugin> plugin, Pointer<const char> id> get_extension;
   Function<void,Pointer<const struct wclap_plugin> plugin> on_main_thread;
};
struct wclap_plugin_factory {
   Function<uint32_t,Pointer<const struct wclap_plugin_factory> factory> get_plugin_count;
   Function<Pointer<const wclap_plugin_descriptor_t> ,
      Pointer<const struct wclap_plugin_factory> factory, uint32_t index> get_plugin_descriptor;
   Function<Pointer<const wclap_plugin_t> ,Pointer<const struct wclap_plugin_factory> factory,
                                                  Pointer<const wclap_host_t>                host,
                                                  Pointer<const char>                       plugin_id> create_plugin;
};
typedef uint64_t wclap_timestamp;
struct wclap_version {
   uint32_t major;
   uint32_t minor;
   uint32_t revision;
};
struct wclap_universal_plugin_id {
   Pointer<const char> abi;
   Pointer<const char> id;
};
struct wclap_preset_discovery_metadata_receiver {
   Pointer<void> receiver_data;
   Function<void,Pointer<const struct wclap_preset_discovery_metadata_receiver> receiver,
                            int32_t                                               os_error,
                            Pointer<const char>                                           error_message> on_error;
   Function<bool,Pointer<const struct wclap_preset_discovery_metadata_receiver> receiver,
                                Pointer<const char>                                           name,
                                Pointer<const char>                                           load_key> begin_preset;
   Function<void,Pointer<const struct wclap_preset_discovery_metadata_receiver> receiver,
                                 Pointer<const wclap_universal_plugin_id_t>                     plugin_id> add_plugin_id;
   Function<void,Pointer<const struct wclap_preset_discovery_metadata_receiver> receiver,
                                    Pointer<const char> soundpack_id> set_soundpack_id;
   Function<void,Pointer<const struct wclap_preset_discovery_metadata_receiver> receiver,
                             uint32_t                                              flags> set_flags;
   Function<void,Pointer<const struct wclap_preset_discovery_metadata_receiver> receiver,
                               Pointer<const char>                                           creator> add_creator;
   Function<void,Pointer<const struct wclap_preset_discovery_metadata_receiver> receiver,
                                   Pointer<const char> description> set_description;
   Function<void,Pointer<const struct wclap_preset_discovery_metadata_receiver> receiver,
                                  wclap_timestamp creation_time,
                                  wclap_timestamp modification_time> set_timestamps;
   Function<void,Pointer<const struct wclap_preset_discovery_metadata_receiver> receiver,
                               Pointer<const char>                                           feature> add_feature;
   Function<void,Pointer<const struct wclap_preset_discovery_metadata_receiver> receiver,
                                  Pointer<const char>                                           key,
                                  Pointer<const char>                                           value> add_extra_info;
};
struct wclap_preset_discovery_filetype {
   Pointer<const char> name;
   Pointer<const char> description;
   Pointer<const char> file_extension;
};
struct wclap_preset_discovery_location {
   uint32_t    flags;
   Pointer<const char> name;
   uint32_t    kind;
   Pointer<const char> location;
};
struct wclap_preset_discovery_soundpack {
   uint32_t       flags;
   Pointer<const char>    id;
   Pointer<const char>    name;
   Pointer<const char>    description;
   Pointer<const char>    homepage_url;
   Pointer<const char>    vendor;
   Pointer<const char>    image_path;
   wclap_timestamp release_timestamp;
};
struct wclap_preset_discovery_provider_descriptor {
   wclap_version_t wclap_version;
   Pointer<const char>    id;
   Pointer<const char>    name;
   Pointer<const char>    vendor;
};
struct wclap_preset_discovery_provider {
   Pointer<const wclap_preset_discovery_provider_descriptor_t> desc;

   Pointer<void> provider_data;
   Function<bool,Pointer<const struct wclap_preset_discovery_provider> provider> init;
   Function<void,Pointer<const struct wclap_preset_discovery_provider> provider> destroy;
   Function<bool,Pointer<const struct wclap_preset_discovery_provider>     provider,
                                uint32_t                                         location_kind,
                                Pointer<const char>                                      location,
                                Pointer<const wclap_preset_discovery_metadata_receiver_t> metadata_receiver> get_metadata;
   Function<Pointer<const void> ,Pointer<const struct wclap_preset_discovery_provider> provider,
                                         Pointer<const char>                                  extension_id> get_extension;
};
struct wclap_preset_discovery_indexer {
   wclap_version_t wclap_version;
   Pointer<const char>    name;
   Pointer<const char>    vendor;
   Pointer<const char>    url;
   Pointer<const char> version;

   Pointer<void> indexer_data;
   Function<bool,Pointer<const struct wclap_preset_discovery_indexer> indexer,
                                    Pointer<const wclap_preset_discovery_filetype_t>     filetype> declare_filetype;
   Function<bool,Pointer<const struct wclap_preset_discovery_indexer> indexer,
                                    Pointer<const wclap_preset_discovery_location_t>     location> declare_location;
   Function<bool,Pointer<const struct wclap_preset_discovery_indexer> indexer,
                                     Pointer<const wclap_preset_discovery_soundpack_t>    soundpack> declare_soundpack;
   Function<Pointer<const void> ,Pointer<const struct wclap_preset_discovery_indexer> indexer,
                                         Pointer<const char>                                 extension_id> get_extension;
};
struct wclap_preset_discovery_factory {
   Function<uint32_t,Pointer<const struct wclap_preset_discovery_factory> factory> count;
   Function<Pointer<const wclap_preset_discovery_provider_descriptor_t> ,
      Pointer<const struct wclap_preset_discovery_factory> factory, uint32_t index> get_descriptor;
   Function<Pointer<const wclap_preset_discovery_provider_t> ,
      Pointer<const struct wclap_preset_discovery_factory> factory,
      Pointer<const wclap_preset_discovery_indexer_t>      indexer,
      Pointer<const char>                                 provider_id> create;
};
struct wclap_version {
   uint32_t major;
   uint32_t minor;
   uint32_t revision;
};
struct wclap_host {
   wclap_version_t wclap_version;

   Pointer<void> host_data;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> version;
   Function<Pointer<const void> ,Pointer<const struct wclap_host> host, Pointer<const char> extension_id> get_extension;
   Function<void,Pointer<const struct wclap_host> host> request_restart;
   Function<void,Pointer<const struct wclap_host> host> request_process;
   Function<void,Pointer<const struct wclap_host> host> request_callback;
};
typedef int64_t wclap_beattime;
typedef int64_t wclap_sectime;
typedef uint32_t wclap_id;
typedef int32_t wclap_note_expression;
struct wclap_event_header {
   uint32_t size;
   uint32_t time;
   uint16_t space_id;
   uint16_t type;
   uint32_t flags;
};
struct wclap_event_note {
   wclap_event_header_t header;

   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;
   double  velocity;
};
struct wclap_event_note_expression {
   wclap_event_header_t header;

   wclap_note_expression expression_id;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_value {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_mod {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double amount;
};
struct wclap_event_param_gesture {
   wclap_event_header_t header;
   wclap_id param_id;
};
struct wclap_event_transport {
   wclap_event_header_t header;

   uint32_t flags;

   wclap_beattime song_pos_beats;
   wclap_sectime  song_pos_seconds;

   double tempo;
   double tempo_inc;

   wclap_beattime loop_start_beats;
   wclap_beattime loop_end_beats;
   wclap_sectime  loop_start_seconds;
   wclap_sectime  loop_end_seconds;

   wclap_beattime bar_start;
   int32_t       bar_number;

   uint16_t tsig_num;
   uint16_t tsig_denom;
};
struct wclap_event_midi {
   wclap_event_header_t header;

   uint16_t port_index;
   uint8_t  data[3];
};
struct wclap_event_midi_sysex {
   wclap_event_header_t header;

   uint16_t       port_index;
   Pointer<const uint8_t> buffer;
   uint32_t       size;
};
struct wclap_event_midi2 {
   wclap_event_header_t header;

   uint16_t port_index;
   uint32_t data[4];
};
struct wclap_input_events {
   Pointer<void> ctx;
   Function<uint32_t,Pointer<const struct wclap_input_events> list> size;
   Function<Pointer<const wclap_event_header_t> ,Pointer<const struct wclap_input_events> list, uint32_t index> get;
};
struct wclap_output_events {
   Pointer<void> ctx;
   Function<bool,Pointer<const struct wclap_output_events> list,
                            Pointer<const wclap_event_header_t>       event> try_push;
};
struct wclap_audio_buffer {
   Pointer<Pointer<float>>  data32;
   Pointer<Pointer<double>> data64;
   uint32_t channel_count;
   uint32_t latency;
   uint64_t constant_mask;
};
typedef int32_t wclap_process_status;
struct wclap_process {
   int64_t steady_time;
   uint32_t frames_count;
   Pointer<const wclap_event_transport_t> transport;
   Pointer<const wclap_audio_buffer_t> audio_inputs;
   Pointer<wclap_audio_buffer_t>       audio_outputs;
   uint32_t                   audio_inputs_count;
   uint32_t                   audio_outputs_count;
   Pointer<const wclap_input_events_t>  in_events;
   Pointer<const wclap_output_events_t> out_events;
};
struct wclap_plugin_descriptor {
   wclap_version_t wclap_version;
   Pointer<const char> id;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> manual_url;
   Pointer<const char> support_url;
   Pointer<const char> version;
   Pointer<const char> description;
   Pointer<const char> Pointer<const> features;
};
struct wclap_plugin {
   Pointer<const wclap_plugin_descriptor_t> desc;

   Pointer<void> plugin_data;
   Function<bool,Pointer<const struct wclap_plugin> plugin> init;
   Function<void,Pointer<const struct wclap_plugin> plugin> destroy;
   Function<bool,Pointer<const struct wclap_plugin> plugin,
                            double                    sample_rate,
                            uint32_t                  min_frames_count,
                            uint32_t                  max_frames_count> activate;
   Function<void,Pointer<const struct wclap_plugin> plugin> deactivate;
   Function<bool,Pointer<const struct wclap_plugin> plugin> start_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> stop_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> reset;
   Function<wclap_process_status,Pointer<const struct wclap_plugin> plugin,
                                          Pointer<const wclap_process_t>     process> process;
   Function<Pointer<const void> ,Pointer<const struct wclap_plugin> plugin, Pointer<const char> id> get_extension;
   Function<void,Pointer<const struct wclap_plugin> plugin> on_main_thread;
};
struct wclap_version {
   uint32_t major;
   uint32_t minor;
   uint32_t revision;
};
struct wclap_host {
   wclap_version_t wclap_version;

   Pointer<void> host_data;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> version;
   Function<Pointer<const void> ,Pointer<const struct wclap_host> host, Pointer<const char> extension_id> get_extension;
   Function<void,Pointer<const struct wclap_host> host> request_restart;
   Function<void,Pointer<const struct wclap_host> host> request_process;
   Function<void,Pointer<const struct wclap_host> host> request_callback;
};
struct wclap_universal_plugin_id {
   Pointer<const char> abi;
   Pointer<const char> id;
};
struct wclap_version {
   uint32_t major;
   uint32_t minor;
   uint32_t revision;
};
struct wclap_host {
   wclap_version_t wclap_version;

   Pointer<void> host_data;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> version;
   Function<Pointer<const void> ,Pointer<const struct wclap_host> host, Pointer<const char> extension_id> get_extension;
   Function<void,Pointer<const struct wclap_host> host> request_restart;
   Function<void,Pointer<const struct wclap_host> host> request_process;
   Function<void,Pointer<const struct wclap_host> host> request_callback;
};
typedef int64_t wclap_beattime;
typedef int64_t wclap_sectime;
typedef uint32_t wclap_id;
typedef int32_t wclap_note_expression;
struct wclap_event_header {
   uint32_t size;
   uint32_t time;
   uint16_t space_id;
   uint16_t type;
   uint32_t flags;
};
struct wclap_event_note {
   wclap_event_header_t header;

   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;
   double  velocity;
};
struct wclap_event_note_expression {
   wclap_event_header_t header;

   wclap_note_expression expression_id;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_value {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_mod {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double amount;
};
struct wclap_event_param_gesture {
   wclap_event_header_t header;
   wclap_id param_id;
};
struct wclap_event_transport {
   wclap_event_header_t header;

   uint32_t flags;

   wclap_beattime song_pos_beats;
   wclap_sectime  song_pos_seconds;

   double tempo;
   double tempo_inc;

   wclap_beattime loop_start_beats;
   wclap_beattime loop_end_beats;
   wclap_sectime  loop_start_seconds;
   wclap_sectime  loop_end_seconds;

   wclap_beattime bar_start;
   int32_t       bar_number;

   uint16_t tsig_num;
   uint16_t tsig_denom;
};
struct wclap_event_midi {
   wclap_event_header_t header;

   uint16_t port_index;
   uint8_t  data[3];
};
struct wclap_event_midi_sysex {
   wclap_event_header_t header;

   uint16_t       port_index;
   Pointer<const uint8_t> buffer;
   uint32_t       size;
};
struct wclap_event_midi2 {
   wclap_event_header_t header;

   uint16_t port_index;
   uint32_t data[4];
};
struct wclap_input_events {
   Pointer<void> ctx;
   Function<uint32_t,Pointer<const struct wclap_input_events> list> size;
   Function<Pointer<const wclap_event_header_t> ,Pointer<const struct wclap_input_events> list, uint32_t index> get;
};
struct wclap_output_events {
   Pointer<void> ctx;
   Function<bool,Pointer<const struct wclap_output_events> list,
                            Pointer<const wclap_event_header_t>       event> try_push;
};
struct wclap_audio_buffer {
   Pointer<Pointer<float>>  data32;
   Pointer<Pointer<double>> data64;
   uint32_t channel_count;
   uint32_t latency;
   uint64_t constant_mask;
};
typedef int32_t wclap_process_status;
struct wclap_process {
   int64_t steady_time;
   uint32_t frames_count;
   Pointer<const wclap_event_transport_t> transport;
   Pointer<const wclap_audio_buffer_t> audio_inputs;
   Pointer<wclap_audio_buffer_t>       audio_outputs;
   uint32_t                   audio_inputs_count;
   uint32_t                   audio_outputs_count;
   Pointer<const wclap_input_events_t>  in_events;
   Pointer<const wclap_output_events_t> out_events;
};
struct wclap_plugin_descriptor {
   wclap_version_t wclap_version;
   Pointer<const char> id;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> manual_url;
   Pointer<const char> support_url;
   Pointer<const char> version;
   Pointer<const char> description;
   Pointer<const char> Pointer<const> features;
};
struct wclap_plugin {
   Pointer<const wclap_plugin_descriptor_t> desc;

   Pointer<void> plugin_data;
   Function<bool,Pointer<const struct wclap_plugin> plugin> init;
   Function<void,Pointer<const struct wclap_plugin> plugin> destroy;
   Function<bool,Pointer<const struct wclap_plugin> plugin,
                            double                    sample_rate,
                            uint32_t                  min_frames_count,
                            uint32_t                  max_frames_count> activate;
   Function<void,Pointer<const struct wclap_plugin> plugin> deactivate;
   Function<bool,Pointer<const struct wclap_plugin> plugin> start_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> stop_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> reset;
   Function<wclap_process_status,Pointer<const struct wclap_plugin> plugin,
                                          Pointer<const wclap_process_t>     process> process;
   Function<Pointer<const void> ,Pointer<const struct wclap_plugin> plugin, Pointer<const char> id> get_extension;
   Function<void,Pointer<const struct wclap_plugin> plugin> on_main_thread;
};
struct wclap_ambisonic_config {
   uint32_t ordering;
   uint32_t normalization;
};
struct wclap_plugin_ambisonic {
   Function<bool,Pointer<const wclap_plugin_t>           plugin,
                                       Pointer<const wclap_ambisonic_config_t> config> is_config_supported;
   Function<bool,Pointer<const wclap_plugin_t>     plugin,
                              bool                     is_input,
                              uint32_t                 port_index,
                              Pointer<wclap_ambisonic_config_t> config> get_config;

};
struct wclap_host_ambisonic {
   Function<void,Pointer<const wclap_host_t> host> changed;
};
struct wclap_version {
   uint32_t major;
   uint32_t minor;
   uint32_t revision;
};
struct wclap_host {
   wclap_version_t wclap_version;

   Pointer<void> host_data;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> version;
   Function<Pointer<const void> ,Pointer<const struct wclap_host> host, Pointer<const char> extension_id> get_extension;
   Function<void,Pointer<const struct wclap_host> host> request_restart;
   Function<void,Pointer<const struct wclap_host> host> request_process;
   Function<void,Pointer<const struct wclap_host> host> request_callback;
};
typedef int64_t wclap_beattime;
typedef int64_t wclap_sectime;
typedef uint32_t wclap_id;
typedef int32_t wclap_note_expression;
struct wclap_event_header {
   uint32_t size;
   uint32_t time;
   uint16_t space_id;
   uint16_t type;
   uint32_t flags;
};
struct wclap_event_note {
   wclap_event_header_t header;

   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;
   double  velocity;
};
struct wclap_event_note_expression {
   wclap_event_header_t header;

   wclap_note_expression expression_id;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_value {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_mod {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double amount;
};
struct wclap_event_param_gesture {
   wclap_event_header_t header;
   wclap_id param_id;
};
struct wclap_event_transport {
   wclap_event_header_t header;

   uint32_t flags;

   wclap_beattime song_pos_beats;
   wclap_sectime  song_pos_seconds;

   double tempo;
   double tempo_inc;

   wclap_beattime loop_start_beats;
   wclap_beattime loop_end_beats;
   wclap_sectime  loop_start_seconds;
   wclap_sectime  loop_end_seconds;

   wclap_beattime bar_start;
   int32_t       bar_number;

   uint16_t tsig_num;
   uint16_t tsig_denom;
};
struct wclap_event_midi {
   wclap_event_header_t header;

   uint16_t port_index;
   uint8_t  data[3];
};
struct wclap_event_midi_sysex {
   wclap_event_header_t header;

   uint16_t       port_index;
   Pointer<const uint8_t> buffer;
   uint32_t       size;
};
struct wclap_event_midi2 {
   wclap_event_header_t header;

   uint16_t port_index;
   uint32_t data[4];
};
struct wclap_input_events {
   Pointer<void> ctx;
   Function<uint32_t,Pointer<const struct wclap_input_events> list> size;
   Function<Pointer<const wclap_event_header_t> ,Pointer<const struct wclap_input_events> list, uint32_t index> get;
};
struct wclap_output_events {
   Pointer<void> ctx;
   Function<bool,Pointer<const struct wclap_output_events> list,
                            Pointer<const wclap_event_header_t>       event> try_push;
};
struct wclap_audio_buffer {
   Pointer<Pointer<float>>  data32;
   Pointer<Pointer<double>> data64;
   uint32_t channel_count;
   uint32_t latency;
   uint64_t constant_mask;
};
typedef int32_t wclap_process_status;
struct wclap_process {
   int64_t steady_time;
   uint32_t frames_count;
   Pointer<const wclap_event_transport_t> transport;
   Pointer<const wclap_audio_buffer_t> audio_inputs;
   Pointer<wclap_audio_buffer_t>       audio_outputs;
   uint32_t                   audio_inputs_count;
   uint32_t                   audio_outputs_count;
   Pointer<const wclap_input_events_t>  in_events;
   Pointer<const wclap_output_events_t> out_events;
};
struct wclap_plugin_descriptor {
   wclap_version_t wclap_version;
   Pointer<const char> id;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> manual_url;
   Pointer<const char> support_url;
   Pointer<const char> version;
   Pointer<const char> description;
   Pointer<const char> Pointer<const> features;
};
struct wclap_plugin {
   Pointer<const wclap_plugin_descriptor_t> desc;

   Pointer<void> plugin_data;
   Function<bool,Pointer<const struct wclap_plugin> plugin> init;
   Function<void,Pointer<const struct wclap_plugin> plugin> destroy;
   Function<bool,Pointer<const struct wclap_plugin> plugin,
                            double                    sample_rate,
                            uint32_t                  min_frames_count,
                            uint32_t                  max_frames_count> activate;
   Function<void,Pointer<const struct wclap_plugin> plugin> deactivate;
   Function<bool,Pointer<const struct wclap_plugin> plugin> start_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> stop_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> reset;
   Function<wclap_process_status,Pointer<const struct wclap_plugin> plugin,
                                          Pointer<const wclap_process_t>     process> process;
   Function<Pointer<const void> ,Pointer<const struct wclap_plugin> plugin, Pointer<const char> id> get_extension;
   Function<void,Pointer<const struct wclap_plugin> plugin> on_main_thread;
};
struct wclap_plugin_audio_ports_activation {
   Function<bool,Pointer<const wclap_plugin_t> plugin> can_activate_while_processing;
   Function<bool,Pointer<const wclap_plugin_t> plugin,
                              bool                 is_input,
                              uint32_t             port_index,
                              bool                 is_active,
                              uint32_t             sample_size> set_active;
};
struct wclap_version {
   uint32_t major;
   uint32_t minor;
   uint32_t revision;
};
struct wclap_host {
   wclap_version_t wclap_version;

   Pointer<void> host_data;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> version;
   Function<Pointer<const void> ,Pointer<const struct wclap_host> host, Pointer<const char> extension_id> get_extension;
   Function<void,Pointer<const struct wclap_host> host> request_restart;
   Function<void,Pointer<const struct wclap_host> host> request_process;
   Function<void,Pointer<const struct wclap_host> host> request_callback;
};
typedef int64_t wclap_beattime;
typedef int64_t wclap_sectime;
typedef uint32_t wclap_id;
typedef int32_t wclap_note_expression;
struct wclap_event_header {
   uint32_t size;
   uint32_t time;
   uint16_t space_id;
   uint16_t type;
   uint32_t flags;
};
struct wclap_event_note {
   wclap_event_header_t header;

   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;
   double  velocity;
};
struct wclap_event_note_expression {
   wclap_event_header_t header;

   wclap_note_expression expression_id;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_value {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_mod {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double amount;
};
struct wclap_event_param_gesture {
   wclap_event_header_t header;
   wclap_id param_id;
};
struct wclap_event_transport {
   wclap_event_header_t header;

   uint32_t flags;

   wclap_beattime song_pos_beats;
   wclap_sectime  song_pos_seconds;

   double tempo;
   double tempo_inc;

   wclap_beattime loop_start_beats;
   wclap_beattime loop_end_beats;
   wclap_sectime  loop_start_seconds;
   wclap_sectime  loop_end_seconds;

   wclap_beattime bar_start;
   int32_t       bar_number;

   uint16_t tsig_num;
   uint16_t tsig_denom;
};
struct wclap_event_midi {
   wclap_event_header_t header;

   uint16_t port_index;
   uint8_t  data[3];
};
struct wclap_event_midi_sysex {
   wclap_event_header_t header;

   uint16_t       port_index;
   Pointer<const uint8_t> buffer;
   uint32_t       size;
};
struct wclap_event_midi2 {
   wclap_event_header_t header;

   uint16_t port_index;
   uint32_t data[4];
};
struct wclap_input_events {
   Pointer<void> ctx;
   Function<uint32_t,Pointer<const struct wclap_input_events> list> size;
   Function<Pointer<const wclap_event_header_t> ,Pointer<const struct wclap_input_events> list, uint32_t index> get;
};
struct wclap_output_events {
   Pointer<void> ctx;
   Function<bool,Pointer<const struct wclap_output_events> list,
                            Pointer<const wclap_event_header_t>       event> try_push;
};
struct wclap_audio_buffer {
   Pointer<Pointer<float>>  data32;
   Pointer<Pointer<double>> data64;
   uint32_t channel_count;
   uint32_t latency;
   uint64_t constant_mask;
};
typedef int32_t wclap_process_status;
struct wclap_process {
   int64_t steady_time;
   uint32_t frames_count;
   Pointer<const wclap_event_transport_t> transport;
   Pointer<const wclap_audio_buffer_t> audio_inputs;
   Pointer<wclap_audio_buffer_t>       audio_outputs;
   uint32_t                   audio_inputs_count;
   uint32_t                   audio_outputs_count;
   Pointer<const wclap_input_events_t>  in_events;
   Pointer<const wclap_output_events_t> out_events;
};
struct wclap_plugin_descriptor {
   wclap_version_t wclap_version;
   Pointer<const char> id;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> manual_url;
   Pointer<const char> support_url;
   Pointer<const char> version;
   Pointer<const char> description;
   Pointer<const char> Pointer<const> features;
};
struct wclap_plugin {
   Pointer<const wclap_plugin_descriptor_t> desc;

   Pointer<void> plugin_data;
   Function<bool,Pointer<const struct wclap_plugin> plugin> init;
   Function<void,Pointer<const struct wclap_plugin> plugin> destroy;
   Function<bool,Pointer<const struct wclap_plugin> plugin,
                            double                    sample_rate,
                            uint32_t                  min_frames_count,
                            uint32_t                  max_frames_count> activate;
   Function<void,Pointer<const struct wclap_plugin> plugin> deactivate;
   Function<bool,Pointer<const struct wclap_plugin> plugin> start_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> stop_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> reset;
   Function<wclap_process_status,Pointer<const struct wclap_plugin> plugin,
                                          Pointer<const wclap_process_t>     process> process;
   Function<Pointer<const void> ,Pointer<const struct wclap_plugin> plugin, Pointer<const char> id> get_extension;
   Function<void,Pointer<const struct wclap_plugin> plugin> on_main_thread;
};
struct wclap_version {
   uint32_t major;
   uint32_t minor;
   uint32_t revision;
};
struct wclap_host {
   wclap_version_t wclap_version;

   Pointer<void> host_data;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> version;
   Function<Pointer<const void> ,Pointer<const struct wclap_host> host, Pointer<const char> extension_id> get_extension;
   Function<void,Pointer<const struct wclap_host> host> request_restart;
   Function<void,Pointer<const struct wclap_host> host> request_process;
   Function<void,Pointer<const struct wclap_host> host> request_callback;
};
typedef int64_t wclap_beattime;
typedef int64_t wclap_sectime;
typedef uint32_t wclap_id;
typedef int32_t wclap_note_expression;
struct wclap_event_header {
   uint32_t size;
   uint32_t time;
   uint16_t space_id;
   uint16_t type;
   uint32_t flags;
};
struct wclap_event_note {
   wclap_event_header_t header;

   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;
   double  velocity;
};
struct wclap_event_note_expression {
   wclap_event_header_t header;

   wclap_note_expression expression_id;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_value {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_mod {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double amount;
};
struct wclap_event_param_gesture {
   wclap_event_header_t header;
   wclap_id param_id;
};
struct wclap_event_transport {
   wclap_event_header_t header;

   uint32_t flags;

   wclap_beattime song_pos_beats;
   wclap_sectime  song_pos_seconds;

   double tempo;
   double tempo_inc;

   wclap_beattime loop_start_beats;
   wclap_beattime loop_end_beats;
   wclap_sectime  loop_start_seconds;
   wclap_sectime  loop_end_seconds;

   wclap_beattime bar_start;
   int32_t       bar_number;

   uint16_t tsig_num;
   uint16_t tsig_denom;
};
struct wclap_event_midi {
   wclap_event_header_t header;

   uint16_t port_index;
   uint8_t  data[3];
};
struct wclap_event_midi_sysex {
   wclap_event_header_t header;

   uint16_t       port_index;
   Pointer<const uint8_t> buffer;
   uint32_t       size;
};
struct wclap_event_midi2 {
   wclap_event_header_t header;

   uint16_t port_index;
   uint32_t data[4];
};
struct wclap_input_events {
   Pointer<void> ctx;
   Function<uint32_t,Pointer<const struct wclap_input_events> list> size;
   Function<Pointer<const wclap_event_header_t> ,Pointer<const struct wclap_input_events> list, uint32_t index> get;
};
struct wclap_output_events {
   Pointer<void> ctx;
   Function<bool,Pointer<const struct wclap_output_events> list,
                            Pointer<const wclap_event_header_t>       event> try_push;
};
struct wclap_audio_buffer {
   Pointer<Pointer<float>>  data32;
   Pointer<Pointer<double>> data64;
   uint32_t channel_count;
   uint32_t latency;
   uint64_t constant_mask;
};
typedef int32_t wclap_process_status;
struct wclap_process {
   int64_t steady_time;
   uint32_t frames_count;
   Pointer<const wclap_event_transport_t> transport;
   Pointer<const wclap_audio_buffer_t> audio_inputs;
   Pointer<wclap_audio_buffer_t>       audio_outputs;
   uint32_t                   audio_inputs_count;
   uint32_t                   audio_outputs_count;
   Pointer<const wclap_input_events_t>  in_events;
   Pointer<const wclap_output_events_t> out_events;
};
struct wclap_plugin_descriptor {
   wclap_version_t wclap_version;
   Pointer<const char> id;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> manual_url;
   Pointer<const char> support_url;
   Pointer<const char> version;
   Pointer<const char> description;
   Pointer<const char> Pointer<const> features;
};
struct wclap_plugin {
   Pointer<const wclap_plugin_descriptor_t> desc;

   Pointer<void> plugin_data;
   Function<bool,Pointer<const struct wclap_plugin> plugin> init;
   Function<void,Pointer<const struct wclap_plugin> plugin> destroy;
   Function<bool,Pointer<const struct wclap_plugin> plugin,
                            double                    sample_rate,
                            uint32_t                  min_frames_count,
                            uint32_t                  max_frames_count> activate;
   Function<void,Pointer<const struct wclap_plugin> plugin> deactivate;
   Function<bool,Pointer<const struct wclap_plugin> plugin> start_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> stop_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> reset;
   Function<wclap_process_status,Pointer<const struct wclap_plugin> plugin,
                                          Pointer<const wclap_process_t>     process> process;
   Function<Pointer<const void> ,Pointer<const struct wclap_plugin> plugin, Pointer<const char> id> get_extension;
   Function<void,Pointer<const struct wclap_plugin> plugin> on_main_thread;
};
struct wclap_audio_port_info {
   wclap_id id;
   char    name[CLAP_NAME_SIZE];

   uint32_t flags;
   uint32_t channel_count;
   Pointer<const char> port_type;
   wclap_id in_place_pair;
};
struct wclap_plugin_audio_ports {
   Function<uint32_t,Pointer<const wclap_plugin_t> plugin, bool is_input> count;
   Function<bool,Pointer<const wclap_plugin_t>    plugin,
                       uint32_t                index,
                       bool                    is_input,
                       Pointer<wclap_audio_port_info_t> info> get;
};
struct wclap_host_audio_ports {
   Function<bool,Pointer<const wclap_host_t> host, uint32_t flag> is_rescan_flag_supported;
   Function<void,Pointer<const wclap_host_t> host, uint32_t flags> rescan;
};
struct wclap_audio_ports_config {
   wclap_id id;
   char    name[CLAP_NAME_SIZE];

   uint32_t input_port_count;
   uint32_t output_port_count;
   bool        has_main_input;
   uint32_t    main_input_channel_count;
   Pointer<const char> main_input_port_type;
   bool        has_main_output;
   uint32_t    main_output_channel_count;
   Pointer<const char> main_output_port_type;
};
struct wclap_plugin_audio_ports_config {
   Function<uint32_t,Pointer<const wclap_plugin_t> plugin> count;
   Function<bool,Pointer<const wclap_plugin_t>       plugin,
                       uint32_t                   index,
                       Pointer<wclap_audio_ports_config_t> config> get;
   Function<bool,Pointer<const wclap_plugin_t> plugin, wclap_id config_id> select;
};
struct wclap_plugin_audio_ports_config_info {
   Function<wclap_id,Pointer<const wclap_plugin_t> plugin> current_config;
   Function<bool,Pointer<const wclap_plugin_t>    plugin,
                       wclap_id                 config_id,
                       uint32_t                port_index,
                       bool                    is_input,
                       Pointer<wclap_audio_port_info_t> info> get;
};
struct wclap_host_audio_ports_config {
   Function<void,Pointer<const wclap_host_t> host> rescan;
};
struct wclap_version {
   uint32_t major;
   uint32_t minor;
   uint32_t revision;
};
struct wclap_host {
   wclap_version_t wclap_version;

   Pointer<void> host_data;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> version;
   Function<Pointer<const void> ,Pointer<const struct wclap_host> host, Pointer<const char> extension_id> get_extension;
   Function<void,Pointer<const struct wclap_host> host> request_restart;
   Function<void,Pointer<const struct wclap_host> host> request_process;
   Function<void,Pointer<const struct wclap_host> host> request_callback;
};
typedef int64_t wclap_beattime;
typedef int64_t wclap_sectime;
typedef uint32_t wclap_id;
typedef int32_t wclap_note_expression;
struct wclap_event_header {
   uint32_t size;
   uint32_t time;
   uint16_t space_id;
   uint16_t type;
   uint32_t flags;
};
struct wclap_event_note {
   wclap_event_header_t header;

   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;
   double  velocity;
};
struct wclap_event_note_expression {
   wclap_event_header_t header;

   wclap_note_expression expression_id;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_value {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_mod {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double amount;
};
struct wclap_event_param_gesture {
   wclap_event_header_t header;
   wclap_id param_id;
};
struct wclap_event_transport {
   wclap_event_header_t header;

   uint32_t flags;

   wclap_beattime song_pos_beats;
   wclap_sectime  song_pos_seconds;

   double tempo;
   double tempo_inc;

   wclap_beattime loop_start_beats;
   wclap_beattime loop_end_beats;
   wclap_sectime  loop_start_seconds;
   wclap_sectime  loop_end_seconds;

   wclap_beattime bar_start;
   int32_t       bar_number;

   uint16_t tsig_num;
   uint16_t tsig_denom;
};
struct wclap_event_midi {
   wclap_event_header_t header;

   uint16_t port_index;
   uint8_t  data[3];
};
struct wclap_event_midi_sysex {
   wclap_event_header_t header;

   uint16_t       port_index;
   Pointer<const uint8_t> buffer;
   uint32_t       size;
};
struct wclap_event_midi2 {
   wclap_event_header_t header;

   uint16_t port_index;
   uint32_t data[4];
};
struct wclap_input_events {
   Pointer<void> ctx;
   Function<uint32_t,Pointer<const struct wclap_input_events> list> size;
   Function<Pointer<const wclap_event_header_t> ,Pointer<const struct wclap_input_events> list, uint32_t index> get;
};
struct wclap_output_events {
   Pointer<void> ctx;
   Function<bool,Pointer<const struct wclap_output_events> list,
                            Pointer<const wclap_event_header_t>       event> try_push;
};
struct wclap_audio_buffer {
   Pointer<Pointer<float>>  data32;
   Pointer<Pointer<double>> data64;
   uint32_t channel_count;
   uint32_t latency;
   uint64_t constant_mask;
};
typedef int32_t wclap_process_status;
struct wclap_process {
   int64_t steady_time;
   uint32_t frames_count;
   Pointer<const wclap_event_transport_t> transport;
   Pointer<const wclap_audio_buffer_t> audio_inputs;
   Pointer<wclap_audio_buffer_t>       audio_outputs;
   uint32_t                   audio_inputs_count;
   uint32_t                   audio_outputs_count;
   Pointer<const wclap_input_events_t>  in_events;
   Pointer<const wclap_output_events_t> out_events;
};
struct wclap_plugin_descriptor {
   wclap_version_t wclap_version;
   Pointer<const char> id;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> manual_url;
   Pointer<const char> support_url;
   Pointer<const char> version;
   Pointer<const char> description;
   Pointer<const char> Pointer<const> features;
};
struct wclap_plugin {
   Pointer<const wclap_plugin_descriptor_t> desc;

   Pointer<void> plugin_data;
   Function<bool,Pointer<const struct wclap_plugin> plugin> init;
   Function<void,Pointer<const struct wclap_plugin> plugin> destroy;
   Function<bool,Pointer<const struct wclap_plugin> plugin,
                            double                    sample_rate,
                            uint32_t                  min_frames_count,
                            uint32_t                  max_frames_count> activate;
   Function<void,Pointer<const struct wclap_plugin> plugin> deactivate;
   Function<bool,Pointer<const struct wclap_plugin> plugin> start_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> stop_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> reset;
   Function<wclap_process_status,Pointer<const struct wclap_plugin> plugin,
                                          Pointer<const wclap_process_t>     process> process;
   Function<Pointer<const void> ,Pointer<const struct wclap_plugin> plugin, Pointer<const char> id> get_extension;
   Function<void,Pointer<const struct wclap_plugin> plugin> on_main_thread;
};
struct wclap_audio_port_info {
   wclap_id id;
   char    name[CLAP_NAME_SIZE];

   uint32_t flags;
   uint32_t channel_count;
   Pointer<const char> port_type;
   wclap_id in_place_pair;
};
struct wclap_plugin_audio_ports {
   Function<uint32_t,Pointer<const wclap_plugin_t> plugin, bool is_input> count;
   Function<bool,Pointer<const wclap_plugin_t>    plugin,
                       uint32_t                index,
                       bool                    is_input,
                       Pointer<wclap_audio_port_info_t> info> get;
};
struct wclap_host_audio_ports {
   Function<bool,Pointer<const wclap_host_t> host, uint32_t flag> is_rescan_flag_supported;
   Function<void,Pointer<const wclap_host_t> host, uint32_t flags> rescan;
};
struct wclap_version {
   uint32_t major;
   uint32_t minor;
   uint32_t revision;
};
struct wclap_host {
   wclap_version_t wclap_version;

   Pointer<void> host_data;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> version;
   Function<Pointer<const void> ,Pointer<const struct wclap_host> host, Pointer<const char> extension_id> get_extension;
   Function<void,Pointer<const struct wclap_host> host> request_restart;
   Function<void,Pointer<const struct wclap_host> host> request_process;
   Function<void,Pointer<const struct wclap_host> host> request_callback;
};
typedef int64_t wclap_beattime;
typedef int64_t wclap_sectime;
typedef uint32_t wclap_id;
typedef int32_t wclap_note_expression;
struct wclap_event_header {
   uint32_t size;
   uint32_t time;
   uint16_t space_id;
   uint16_t type;
   uint32_t flags;
};
struct wclap_event_note {
   wclap_event_header_t header;

   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;
   double  velocity;
};
struct wclap_event_note_expression {
   wclap_event_header_t header;

   wclap_note_expression expression_id;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_value {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_mod {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double amount;
};
struct wclap_event_param_gesture {
   wclap_event_header_t header;
   wclap_id param_id;
};
struct wclap_event_transport {
   wclap_event_header_t header;

   uint32_t flags;

   wclap_beattime song_pos_beats;
   wclap_sectime  song_pos_seconds;

   double tempo;
   double tempo_inc;

   wclap_beattime loop_start_beats;
   wclap_beattime loop_end_beats;
   wclap_sectime  loop_start_seconds;
   wclap_sectime  loop_end_seconds;

   wclap_beattime bar_start;
   int32_t       bar_number;

   uint16_t tsig_num;
   uint16_t tsig_denom;
};
struct wclap_event_midi {
   wclap_event_header_t header;

   uint16_t port_index;
   uint8_t  data[3];
};
struct wclap_event_midi_sysex {
   wclap_event_header_t header;

   uint16_t       port_index;
   Pointer<const uint8_t> buffer;
   uint32_t       size;
};
struct wclap_event_midi2 {
   wclap_event_header_t header;

   uint16_t port_index;
   uint32_t data[4];
};
struct wclap_input_events {
   Pointer<void> ctx;
   Function<uint32_t,Pointer<const struct wclap_input_events> list> size;
   Function<Pointer<const wclap_event_header_t> ,Pointer<const struct wclap_input_events> list, uint32_t index> get;
};
struct wclap_output_events {
   Pointer<void> ctx;
   Function<bool,Pointer<const struct wclap_output_events> list,
                            Pointer<const wclap_event_header_t>       event> try_push;
};
struct wclap_audio_buffer {
   Pointer<Pointer<float>>  data32;
   Pointer<Pointer<double>> data64;
   uint32_t channel_count;
   uint32_t latency;
   uint64_t constant_mask;
};
typedef int32_t wclap_process_status;
struct wclap_process {
   int64_t steady_time;
   uint32_t frames_count;
   Pointer<const wclap_event_transport_t> transport;
   Pointer<const wclap_audio_buffer_t> audio_inputs;
   Pointer<wclap_audio_buffer_t>       audio_outputs;
   uint32_t                   audio_inputs_count;
   uint32_t                   audio_outputs_count;
   Pointer<const wclap_input_events_t>  in_events;
   Pointer<const wclap_output_events_t> out_events;
};
struct wclap_plugin_descriptor {
   wclap_version_t wclap_version;
   Pointer<const char> id;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> manual_url;
   Pointer<const char> support_url;
   Pointer<const char> version;
   Pointer<const char> description;
   Pointer<const char> Pointer<const> features;
};
struct wclap_plugin {
   Pointer<const wclap_plugin_descriptor_t> desc;

   Pointer<void> plugin_data;
   Function<bool,Pointer<const struct wclap_plugin> plugin> init;
   Function<void,Pointer<const struct wclap_plugin> plugin> destroy;
   Function<bool,Pointer<const struct wclap_plugin> plugin,
                            double                    sample_rate,
                            uint32_t                  min_frames_count,
                            uint32_t                  max_frames_count> activate;
   Function<void,Pointer<const struct wclap_plugin> plugin> deactivate;
   Function<bool,Pointer<const struct wclap_plugin> plugin> start_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> stop_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> reset;
   Function<wclap_process_status,Pointer<const struct wclap_plugin> plugin,
                                          Pointer<const wclap_process_t>     process> process;
   Function<Pointer<const void> ,Pointer<const struct wclap_plugin> plugin, Pointer<const char> id> get_extension;
   Function<void,Pointer<const struct wclap_plugin> plugin> on_main_thread;
};
struct wclap_audio_port_info {
   wclap_id id;
   char    name[CLAP_NAME_SIZE];

   uint32_t flags;
   uint32_t channel_count;
   Pointer<const char> port_type;
   wclap_id in_place_pair;
};
struct wclap_plugin_audio_ports {
   Function<uint32_t,Pointer<const wclap_plugin_t> plugin, bool is_input> count;
   Function<bool,Pointer<const wclap_plugin_t>    plugin,
                       uint32_t                index,
                       bool                    is_input,
                       Pointer<wclap_audio_port_info_t> info> get;
};
struct wclap_host_audio_ports {
   Function<bool,Pointer<const wclap_host_t> host, uint32_t flag> is_rescan_flag_supported;
   Function<void,Pointer<const wclap_host_t> host, uint32_t flags> rescan;
};
struct wclap_audio_port_configuration_request {
   bool     is_input;
   uint32_t port_index;
   uint32_t channel_count;
   Pointer<const char> port_type;
   Pointer<const void> port_details;
};
struct wclap_plugin_configurable_audio_ports {
   Function<bool,
      Pointer<const wclap_plugin_t>                                plugin,
      Pointer<const struct wclap_audio_port_configuration_request> requests,
      uint32_t                                            request_count> can_apply_configuration;
   Function<bool,Pointer<const wclap_plugin_t>                                plugin,
                                       Pointer<const struct wclap_audio_port_configuration_request> requests,
                                       uint32_t request_count> apply_configuration;
};
struct wclap_version {
   uint32_t major;
   uint32_t minor;
   uint32_t revision;
};
struct wclap_host {
   wclap_version_t wclap_version;

   Pointer<void> host_data;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> version;
   Function<Pointer<const void> ,Pointer<const struct wclap_host> host, Pointer<const char> extension_id> get_extension;
   Function<void,Pointer<const struct wclap_host> host> request_restart;
   Function<void,Pointer<const struct wclap_host> host> request_process;
   Function<void,Pointer<const struct wclap_host> host> request_callback;
};
typedef int64_t wclap_beattime;
typedef int64_t wclap_sectime;
typedef uint32_t wclap_id;
typedef int32_t wclap_note_expression;
struct wclap_event_header {
   uint32_t size;
   uint32_t time;
   uint16_t space_id;
   uint16_t type;
   uint32_t flags;
};
struct wclap_event_note {
   wclap_event_header_t header;

   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;
   double  velocity;
};
struct wclap_event_note_expression {
   wclap_event_header_t header;

   wclap_note_expression expression_id;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_value {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_mod {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double amount;
};
struct wclap_event_param_gesture {
   wclap_event_header_t header;
   wclap_id param_id;
};
struct wclap_event_transport {
   wclap_event_header_t header;

   uint32_t flags;

   wclap_beattime song_pos_beats;
   wclap_sectime  song_pos_seconds;

   double tempo;
   double tempo_inc;

   wclap_beattime loop_start_beats;
   wclap_beattime loop_end_beats;
   wclap_sectime  loop_start_seconds;
   wclap_sectime  loop_end_seconds;

   wclap_beattime bar_start;
   int32_t       bar_number;

   uint16_t tsig_num;
   uint16_t tsig_denom;
};
struct wclap_event_midi {
   wclap_event_header_t header;

   uint16_t port_index;
   uint8_t  data[3];
};
struct wclap_event_midi_sysex {
   wclap_event_header_t header;

   uint16_t       port_index;
   Pointer<const uint8_t> buffer;
   uint32_t       size;
};
struct wclap_event_midi2 {
   wclap_event_header_t header;

   uint16_t port_index;
   uint32_t data[4];
};
struct wclap_input_events {
   Pointer<void> ctx;
   Function<uint32_t,Pointer<const struct wclap_input_events> list> size;
   Function<Pointer<const wclap_event_header_t> ,Pointer<const struct wclap_input_events> list, uint32_t index> get;
};
struct wclap_output_events {
   Pointer<void> ctx;
   Function<bool,Pointer<const struct wclap_output_events> list,
                            Pointer<const wclap_event_header_t>       event> try_push;
};
struct wclap_audio_buffer {
   Pointer<Pointer<float>>  data32;
   Pointer<Pointer<double>> data64;
   uint32_t channel_count;
   uint32_t latency;
   uint64_t constant_mask;
};
typedef int32_t wclap_process_status;
struct wclap_process {
   int64_t steady_time;
   uint32_t frames_count;
   Pointer<const wclap_event_transport_t> transport;
   Pointer<const wclap_audio_buffer_t> audio_inputs;
   Pointer<wclap_audio_buffer_t>       audio_outputs;
   uint32_t                   audio_inputs_count;
   uint32_t                   audio_outputs_count;
   Pointer<const wclap_input_events_t>  in_events;
   Pointer<const wclap_output_events_t> out_events;
};
struct wclap_plugin_descriptor {
   wclap_version_t wclap_version;
   Pointer<const char> id;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> manual_url;
   Pointer<const char> support_url;
   Pointer<const char> version;
   Pointer<const char> description;
   Pointer<const char> Pointer<const> features;
};
struct wclap_plugin {
   Pointer<const wclap_plugin_descriptor_t> desc;

   Pointer<void> plugin_data;
   Function<bool,Pointer<const struct wclap_plugin> plugin> init;
   Function<void,Pointer<const struct wclap_plugin> plugin> destroy;
   Function<bool,Pointer<const struct wclap_plugin> plugin,
                            double                    sample_rate,
                            uint32_t                  min_frames_count,
                            uint32_t                  max_frames_count> activate;
   Function<void,Pointer<const struct wclap_plugin> plugin> deactivate;
   Function<bool,Pointer<const struct wclap_plugin> plugin> start_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> stop_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> reset;
   Function<wclap_process_status,Pointer<const struct wclap_plugin> plugin,
                                          Pointer<const wclap_process_t>     process> process;
   Function<Pointer<const void> ,Pointer<const struct wclap_plugin> plugin, Pointer<const char> id> get_extension;
   Function<void,Pointer<const struct wclap_plugin> plugin> on_main_thread;
};
typedef uint32_t wclap_context_menu_item_kind_t;
struct wclap_context_menu_target {
   uint32_t kind;
   wclap_id  id;
};
struct wclap_context_menu_entry {
   Pointer<const char> label;
   bool        is_enabled;
   wclap_id     action_id;
};
struct wclap_context_menu_check_entry {
   Pointer<const char> label;
   bool        is_enabled;
   bool        is_checked;
   wclap_id     action_id;
};
struct wclap_context_menu_item_title {
   Pointer<const char> title;
   bool        is_enabled;
};
struct wclap_context_menu_submenu {
   Pointer<const char> label;
   bool        is_enabled;
};
struct wclap_context_menu_builder {
   Pointer<void> ctx;
   Function<bool,Pointer<const struct wclap_context_menu_builder> builder,
                            wclap_context_menu_item_kind_t           item_kind,
                            Pointer<const void>                             item_data> add_item;
   Function<bool,Pointer<const struct wclap_context_menu_builder> builder,
                            wclap_context_menu_item_kind_t           item_kind> supports;
};
struct wclap_plugin_context_menu {
   Function<bool,Pointer<const wclap_plugin_t>               plugin,
                            Pointer<const wclap_context_menu_target_t>  target,
                            Pointer<const wclap_context_menu_builder_t> builder> populate;
   Function<bool,Pointer<const wclap_plugin_t>              plugin,
                           Pointer<const wclap_context_menu_target_t> target,
                           wclap_id                           action_id> perform;
};
struct wclap_host_context_menu {
   Function<bool,Pointer<const wclap_host_t>                 host,
                            Pointer<const wclap_context_menu_target_t>  target,
                            Pointer<const wclap_context_menu_builder_t> builder> populate;
   Function<bool,Pointer<const wclap_host_t>                host,
                           Pointer<const wclap_context_menu_target_t> target,
                           wclap_id                           action_id> perform;
   Function<bool,Pointer<const wclap_host_t> host> can_popup;
   Function<bool,Pointer<const wclap_host_t>                host,
                         Pointer<const wclap_context_menu_target_t> target,
                         int32_t                           screen_index,
                         int32_t                           x,
                         int32_t                           y> popup;
};
struct wclap_version {
   uint32_t major;
   uint32_t minor;
   uint32_t revision;
};
struct wclap_host {
   wclap_version_t wclap_version;

   Pointer<void> host_data;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> version;
   Function<Pointer<const void> ,Pointer<const struct wclap_host> host, Pointer<const char> extension_id> get_extension;
   Function<void,Pointer<const struct wclap_host> host> request_restart;
   Function<void,Pointer<const struct wclap_host> host> request_process;
   Function<void,Pointer<const struct wclap_host> host> request_callback;
};
typedef int64_t wclap_beattime;
typedef int64_t wclap_sectime;
typedef uint32_t wclap_id;
typedef int32_t wclap_note_expression;
struct wclap_event_header {
   uint32_t size;
   uint32_t time;
   uint16_t space_id;
   uint16_t type;
   uint32_t flags;
};
struct wclap_event_note {
   wclap_event_header_t header;

   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;
   double  velocity;
};
struct wclap_event_note_expression {
   wclap_event_header_t header;

   wclap_note_expression expression_id;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_value {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_mod {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double amount;
};
struct wclap_event_param_gesture {
   wclap_event_header_t header;
   wclap_id param_id;
};
struct wclap_event_transport {
   wclap_event_header_t header;

   uint32_t flags;

   wclap_beattime song_pos_beats;
   wclap_sectime  song_pos_seconds;

   double tempo;
   double tempo_inc;

   wclap_beattime loop_start_beats;
   wclap_beattime loop_end_beats;
   wclap_sectime  loop_start_seconds;
   wclap_sectime  loop_end_seconds;

   wclap_beattime bar_start;
   int32_t       bar_number;

   uint16_t tsig_num;
   uint16_t tsig_denom;
};
struct wclap_event_midi {
   wclap_event_header_t header;

   uint16_t port_index;
   uint8_t  data[3];
};
struct wclap_event_midi_sysex {
   wclap_event_header_t header;

   uint16_t       port_index;
   Pointer<const uint8_t> buffer;
   uint32_t       size;
};
struct wclap_event_midi2 {
   wclap_event_header_t header;

   uint16_t port_index;
   uint32_t data[4];
};
struct wclap_input_events {
   Pointer<void> ctx;
   Function<uint32_t,Pointer<const struct wclap_input_events> list> size;
   Function<Pointer<const wclap_event_header_t> ,Pointer<const struct wclap_input_events> list, uint32_t index> get;
};
struct wclap_output_events {
   Pointer<void> ctx;
   Function<bool,Pointer<const struct wclap_output_events> list,
                            Pointer<const wclap_event_header_t>       event> try_push;
};
struct wclap_audio_buffer {
   Pointer<Pointer<float>>  data32;
   Pointer<Pointer<double>> data64;
   uint32_t channel_count;
   uint32_t latency;
   uint64_t constant_mask;
};
typedef int32_t wclap_process_status;
struct wclap_process {
   int64_t steady_time;
   uint32_t frames_count;
   Pointer<const wclap_event_transport_t> transport;
   Pointer<const wclap_audio_buffer_t> audio_inputs;
   Pointer<wclap_audio_buffer_t>       audio_outputs;
   uint32_t                   audio_inputs_count;
   uint32_t                   audio_outputs_count;
   Pointer<const wclap_input_events_t>  in_events;
   Pointer<const wclap_output_events_t> out_events;
};
struct wclap_plugin_descriptor {
   wclap_version_t wclap_version;
   Pointer<const char> id;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> manual_url;
   Pointer<const char> support_url;
   Pointer<const char> version;
   Pointer<const char> description;
   Pointer<const char> Pointer<const> features;
};
struct wclap_plugin {
   Pointer<const wclap_plugin_descriptor_t> desc;

   Pointer<void> plugin_data;
   Function<bool,Pointer<const struct wclap_plugin> plugin> init;
   Function<void,Pointer<const struct wclap_plugin> plugin> destroy;
   Function<bool,Pointer<const struct wclap_plugin> plugin,
                            double                    sample_rate,
                            uint32_t                  min_frames_count,
                            uint32_t                  max_frames_count> activate;
   Function<void,Pointer<const struct wclap_plugin> plugin> deactivate;
   Function<bool,Pointer<const struct wclap_plugin> plugin> start_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> stop_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> reset;
   Function<wclap_process_status,Pointer<const struct wclap_plugin> plugin,
                                          Pointer<const wclap_process_t>     process> process;
   Function<Pointer<const void> ,Pointer<const struct wclap_plugin> plugin, Pointer<const char> id> get_extension;
   Function<void,Pointer<const struct wclap_plugin> plugin> on_main_thread;
};
struct wclap_host_event_registry {
   Function<bool,Pointer<const wclap_host_t> host, Pointer<const char> space_name, Pointer<uint16_t> space_id> query;
};
struct wclap_version {
   uint32_t major;
   uint32_t minor;
   uint32_t revision;
};
struct wclap_host {
   wclap_version_t wclap_version;

   Pointer<void> host_data;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> version;
   Function<Pointer<const void> ,Pointer<const struct wclap_host> host, Pointer<const char> extension_id> get_extension;
   Function<void,Pointer<const struct wclap_host> host> request_restart;
   Function<void,Pointer<const struct wclap_host> host> request_process;
   Function<void,Pointer<const struct wclap_host> host> request_callback;
};
typedef int64_t wclap_beattime;
typedef int64_t wclap_sectime;
typedef uint32_t wclap_id;
typedef int32_t wclap_note_expression;
struct wclap_event_header {
   uint32_t size;
   uint32_t time;
   uint16_t space_id;
   uint16_t type;
   uint32_t flags;
};
struct wclap_event_note {
   wclap_event_header_t header;

   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;
   double  velocity;
};
struct wclap_event_note_expression {
   wclap_event_header_t header;

   wclap_note_expression expression_id;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_value {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_mod {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double amount;
};
struct wclap_event_param_gesture {
   wclap_event_header_t header;
   wclap_id param_id;
};
struct wclap_event_transport {
   wclap_event_header_t header;

   uint32_t flags;

   wclap_beattime song_pos_beats;
   wclap_sectime  song_pos_seconds;

   double tempo;
   double tempo_inc;

   wclap_beattime loop_start_beats;
   wclap_beattime loop_end_beats;
   wclap_sectime  loop_start_seconds;
   wclap_sectime  loop_end_seconds;

   wclap_beattime bar_start;
   int32_t       bar_number;

   uint16_t tsig_num;
   uint16_t tsig_denom;
};
struct wclap_event_midi {
   wclap_event_header_t header;

   uint16_t port_index;
   uint8_t  data[3];
};
struct wclap_event_midi_sysex {
   wclap_event_header_t header;

   uint16_t       port_index;
   Pointer<const uint8_t> buffer;
   uint32_t       size;
};
struct wclap_event_midi2 {
   wclap_event_header_t header;

   uint16_t port_index;
   uint32_t data[4];
};
struct wclap_input_events {
   Pointer<void> ctx;
   Function<uint32_t,Pointer<const struct wclap_input_events> list> size;
   Function<Pointer<const wclap_event_header_t> ,Pointer<const struct wclap_input_events> list, uint32_t index> get;
};
struct wclap_output_events {
   Pointer<void> ctx;
   Function<bool,Pointer<const struct wclap_output_events> list,
                            Pointer<const wclap_event_header_t>       event> try_push;
};
struct wclap_audio_buffer {
   Pointer<Pointer<float>>  data32;
   Pointer<Pointer<double>> data64;
   uint32_t channel_count;
   uint32_t latency;
   uint64_t constant_mask;
};
typedef int32_t wclap_process_status;
struct wclap_process {
   int64_t steady_time;
   uint32_t frames_count;
   Pointer<const wclap_event_transport_t> transport;
   Pointer<const wclap_audio_buffer_t> audio_inputs;
   Pointer<wclap_audio_buffer_t>       audio_outputs;
   uint32_t                   audio_inputs_count;
   uint32_t                   audio_outputs_count;
   Pointer<const wclap_input_events_t>  in_events;
   Pointer<const wclap_output_events_t> out_events;
};
struct wclap_plugin_descriptor {
   wclap_version_t wclap_version;
   Pointer<const char> id;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> manual_url;
   Pointer<const char> support_url;
   Pointer<const char> version;
   Pointer<const char> description;
   Pointer<const char> Pointer<const> features;
};
struct wclap_plugin {
   Pointer<const wclap_plugin_descriptor_t> desc;

   Pointer<void> plugin_data;
   Function<bool,Pointer<const struct wclap_plugin> plugin> init;
   Function<void,Pointer<const struct wclap_plugin> plugin> destroy;
   Function<bool,Pointer<const struct wclap_plugin> plugin,
                            double                    sample_rate,
                            uint32_t                  min_frames_count,
                            uint32_t                  max_frames_count> activate;
   Function<void,Pointer<const struct wclap_plugin> plugin> deactivate;
   Function<bool,Pointer<const struct wclap_plugin> plugin> start_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> stop_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> reset;
   Function<wclap_process_status,Pointer<const struct wclap_plugin> plugin,
                                          Pointer<const wclap_process_t>     process> process;
   Function<Pointer<const void> ,Pointer<const struct wclap_plugin> plugin, Pointer<const char> id> get_extension;
   Function<void,Pointer<const struct wclap_plugin> plugin> on_main_thread;
};
typedef unsigned long wclap_xwnd;
struct wclap_window {
   Pointer<const char> api;
   union {
      wclap_nsview cocoa;
      wclap_xwnd   x11;
      wclap_hwnd   win32;
      Pointer<void>       ptr;
   };
};
struct wclap_gui_resize_hints {
   bool can_resize_horizontally;
   bool can_resize_vertically;
   bool     preserve_aspect_ratio;
   uint32_t aspect_ratio_width;
   uint32_t aspect_ratio_height;
};
struct wclap_plugin_gui {
   Function<bool,Pointer<const wclap_plugin_t> plugin, Pointer<const char> api, bool is_floating> is_api_supported;
   Function<bool,Pointer<const wclap_plugin_t> plugin,
                                     Pointer<Pointer<const char>>         api,
                                     Pointer<bool>                is_floating> get_preferred_api;
   Function<bool,Pointer<const wclap_plugin_t> plugin, Pointer<const char> api, bool is_floating> create;
   Function<void,Pointer<const wclap_plugin_t> plugin> destroy;
   Function<bool,Pointer<const wclap_plugin_t> plugin, double scale> set_scale;
   Function<bool,Pointer<const wclap_plugin_t> plugin, Pointer<uint32_t> width, Pointer<uint32_t> height> get_size;
   Function<bool,Pointer<const wclap_plugin_t> plugin> can_resize;
   Function<bool,Pointer<const wclap_plugin_t> plugin, Pointer<wclap_gui_resize_hints_t> hints> get_resize_hints;
   Function<bool,Pointer<const wclap_plugin_t> plugin, Pointer<uint32_t> width, Pointer<uint32_t> height> adjust_size;
   Function<bool,Pointer<const wclap_plugin_t> plugin, uint32_t width, uint32_t height> set_size;
   Function<bool,Pointer<const wclap_plugin_t> plugin, Pointer<const wclap_window_t> window> set_parent;
   Function<bool,Pointer<const wclap_plugin_t> plugin, Pointer<const wclap_window_t> window> set_transient;
   Function<void,Pointer<const wclap_plugin_t> plugin, Pointer<const char> title> suggest_title;
   Function<bool,Pointer<const wclap_plugin_t> plugin> show;
   Function<bool,Pointer<const wclap_plugin_t> plugin> hide;
};
struct wclap_host_gui {
   Function<void,Pointer<const wclap_host_t> host> resize_hints_changed;
   Function<bool,Pointer<const wclap_host_t> host, uint32_t width, uint32_t height> request_resize;
   Function<bool,Pointer<const wclap_host_t> host> request_show;
   Function<bool,Pointer<const wclap_host_t> host> request_hide;
   Function<void,Pointer<const wclap_host_t> host, bool was_destroyed> closed;
};
struct wclap_version {
   uint32_t major;
   uint32_t minor;
   uint32_t revision;
};
struct wclap_host {
   wclap_version_t wclap_version;

   Pointer<void> host_data;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> version;
   Function<Pointer<const void> ,Pointer<const struct wclap_host> host, Pointer<const char> extension_id> get_extension;
   Function<void,Pointer<const struct wclap_host> host> request_restart;
   Function<void,Pointer<const struct wclap_host> host> request_process;
   Function<void,Pointer<const struct wclap_host> host> request_callback;
};
typedef int64_t wclap_beattime;
typedef int64_t wclap_sectime;
typedef uint32_t wclap_id;
typedef int32_t wclap_note_expression;
struct wclap_event_header {
   uint32_t size;
   uint32_t time;
   uint16_t space_id;
   uint16_t type;
   uint32_t flags;
};
struct wclap_event_note {
   wclap_event_header_t header;

   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;
   double  velocity;
};
struct wclap_event_note_expression {
   wclap_event_header_t header;

   wclap_note_expression expression_id;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_value {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_mod {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double amount;
};
struct wclap_event_param_gesture {
   wclap_event_header_t header;
   wclap_id param_id;
};
struct wclap_event_transport {
   wclap_event_header_t header;

   uint32_t flags;

   wclap_beattime song_pos_beats;
   wclap_sectime  song_pos_seconds;

   double tempo;
   double tempo_inc;

   wclap_beattime loop_start_beats;
   wclap_beattime loop_end_beats;
   wclap_sectime  loop_start_seconds;
   wclap_sectime  loop_end_seconds;

   wclap_beattime bar_start;
   int32_t       bar_number;

   uint16_t tsig_num;
   uint16_t tsig_denom;
};
struct wclap_event_midi {
   wclap_event_header_t header;

   uint16_t port_index;
   uint8_t  data[3];
};
struct wclap_event_midi_sysex {
   wclap_event_header_t header;

   uint16_t       port_index;
   Pointer<const uint8_t> buffer;
   uint32_t       size;
};
struct wclap_event_midi2 {
   wclap_event_header_t header;

   uint16_t port_index;
   uint32_t data[4];
};
struct wclap_input_events {
   Pointer<void> ctx;
   Function<uint32_t,Pointer<const struct wclap_input_events> list> size;
   Function<Pointer<const wclap_event_header_t> ,Pointer<const struct wclap_input_events> list, uint32_t index> get;
};
struct wclap_output_events {
   Pointer<void> ctx;
   Function<bool,Pointer<const struct wclap_output_events> list,
                            Pointer<const wclap_event_header_t>       event> try_push;
};
struct wclap_audio_buffer {
   Pointer<Pointer<float>>  data32;
   Pointer<Pointer<double>> data64;
   uint32_t channel_count;
   uint32_t latency;
   uint64_t constant_mask;
};
typedef int32_t wclap_process_status;
struct wclap_process {
   int64_t steady_time;
   uint32_t frames_count;
   Pointer<const wclap_event_transport_t> transport;
   Pointer<const wclap_audio_buffer_t> audio_inputs;
   Pointer<wclap_audio_buffer_t>       audio_outputs;
   uint32_t                   audio_inputs_count;
   uint32_t                   audio_outputs_count;
   Pointer<const wclap_input_events_t>  in_events;
   Pointer<const wclap_output_events_t> out_events;
};
struct wclap_plugin_descriptor {
   wclap_version_t wclap_version;
   Pointer<const char> id;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> manual_url;
   Pointer<const char> support_url;
   Pointer<const char> version;
   Pointer<const char> description;
   Pointer<const char> Pointer<const> features;
};
struct wclap_plugin {
   Pointer<const wclap_plugin_descriptor_t> desc;

   Pointer<void> plugin_data;
   Function<bool,Pointer<const struct wclap_plugin> plugin> init;
   Function<void,Pointer<const struct wclap_plugin> plugin> destroy;
   Function<bool,Pointer<const struct wclap_plugin> plugin,
                            double                    sample_rate,
                            uint32_t                  min_frames_count,
                            uint32_t                  max_frames_count> activate;
   Function<void,Pointer<const struct wclap_plugin> plugin> deactivate;
   Function<bool,Pointer<const struct wclap_plugin> plugin> start_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> stop_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> reset;
   Function<wclap_process_status,Pointer<const struct wclap_plugin> plugin,
                                          Pointer<const wclap_process_t>     process> process;
   Function<Pointer<const void> ,Pointer<const struct wclap_plugin> plugin, Pointer<const char> id> get_extension;
   Function<void,Pointer<const struct wclap_plugin> plugin> on_main_thread;
};
struct wclap_plugin_latency {
   Function<uint32_t,Pointer<const wclap_plugin_t> plugin> get;
};
struct wclap_host_latency {
   Function<void,Pointer<const wclap_host_t> host> changed;
};
struct wclap_version {
   uint32_t major;
   uint32_t minor;
   uint32_t revision;
};
struct wclap_host {
   wclap_version_t wclap_version;

   Pointer<void> host_data;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> version;
   Function<Pointer<const void> ,Pointer<const struct wclap_host> host, Pointer<const char> extension_id> get_extension;
   Function<void,Pointer<const struct wclap_host> host> request_restart;
   Function<void,Pointer<const struct wclap_host> host> request_process;
   Function<void,Pointer<const struct wclap_host> host> request_callback;
};
typedef int64_t wclap_beattime;
typedef int64_t wclap_sectime;
typedef uint32_t wclap_id;
typedef int32_t wclap_note_expression;
struct wclap_event_header {
   uint32_t size;
   uint32_t time;
   uint16_t space_id;
   uint16_t type;
   uint32_t flags;
};
struct wclap_event_note {
   wclap_event_header_t header;

   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;
   double  velocity;
};
struct wclap_event_note_expression {
   wclap_event_header_t header;

   wclap_note_expression expression_id;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_value {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_mod {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double amount;
};
struct wclap_event_param_gesture {
   wclap_event_header_t header;
   wclap_id param_id;
};
struct wclap_event_transport {
   wclap_event_header_t header;

   uint32_t flags;

   wclap_beattime song_pos_beats;
   wclap_sectime  song_pos_seconds;

   double tempo;
   double tempo_inc;

   wclap_beattime loop_start_beats;
   wclap_beattime loop_end_beats;
   wclap_sectime  loop_start_seconds;
   wclap_sectime  loop_end_seconds;

   wclap_beattime bar_start;
   int32_t       bar_number;

   uint16_t tsig_num;
   uint16_t tsig_denom;
};
struct wclap_event_midi {
   wclap_event_header_t header;

   uint16_t port_index;
   uint8_t  data[3];
};
struct wclap_event_midi_sysex {
   wclap_event_header_t header;

   uint16_t       port_index;
   Pointer<const uint8_t> buffer;
   uint32_t       size;
};
struct wclap_event_midi2 {
   wclap_event_header_t header;

   uint16_t port_index;
   uint32_t data[4];
};
struct wclap_input_events {
   Pointer<void> ctx;
   Function<uint32_t,Pointer<const struct wclap_input_events> list> size;
   Function<Pointer<const wclap_event_header_t> ,Pointer<const struct wclap_input_events> list, uint32_t index> get;
};
struct wclap_output_events {
   Pointer<void> ctx;
   Function<bool,Pointer<const struct wclap_output_events> list,
                            Pointer<const wclap_event_header_t>       event> try_push;
};
struct wclap_audio_buffer {
   Pointer<Pointer<float>>  data32;
   Pointer<Pointer<double>> data64;
   uint32_t channel_count;
   uint32_t latency;
   uint64_t constant_mask;
};
typedef int32_t wclap_process_status;
struct wclap_process {
   int64_t steady_time;
   uint32_t frames_count;
   Pointer<const wclap_event_transport_t> transport;
   Pointer<const wclap_audio_buffer_t> audio_inputs;
   Pointer<wclap_audio_buffer_t>       audio_outputs;
   uint32_t                   audio_inputs_count;
   uint32_t                   audio_outputs_count;
   Pointer<const wclap_input_events_t>  in_events;
   Pointer<const wclap_output_events_t> out_events;
};
struct wclap_plugin_descriptor {
   wclap_version_t wclap_version;
   Pointer<const char> id;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> manual_url;
   Pointer<const char> support_url;
   Pointer<const char> version;
   Pointer<const char> description;
   Pointer<const char> Pointer<const> features;
};
struct wclap_plugin {
   Pointer<const wclap_plugin_descriptor_t> desc;

   Pointer<void> plugin_data;
   Function<bool,Pointer<const struct wclap_plugin> plugin> init;
   Function<void,Pointer<const struct wclap_plugin> plugin> destroy;
   Function<bool,Pointer<const struct wclap_plugin> plugin,
                            double                    sample_rate,
                            uint32_t                  min_frames_count,
                            uint32_t                  max_frames_count> activate;
   Function<void,Pointer<const struct wclap_plugin> plugin> deactivate;
   Function<bool,Pointer<const struct wclap_plugin> plugin> start_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> stop_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> reset;
   Function<wclap_process_status,Pointer<const struct wclap_plugin> plugin,
                                          Pointer<const wclap_process_t>     process> process;
   Function<Pointer<const void> ,Pointer<const struct wclap_plugin> plugin, Pointer<const char> id> get_extension;
   Function<void,Pointer<const struct wclap_plugin> plugin> on_main_thread;
};
typedef int32_t wclap_log_severity;
struct wclap_host_log {
   Function<void,Pointer<const wclap_host_t> host, wclap_log_severity severity, Pointer<const char> msg> log;
};
struct wclap_version {
   uint32_t major;
   uint32_t minor;
   uint32_t revision;
};
struct wclap_host {
   wclap_version_t wclap_version;

   Pointer<void> host_data;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> version;
   Function<Pointer<const void> ,Pointer<const struct wclap_host> host, Pointer<const char> extension_id> get_extension;
   Function<void,Pointer<const struct wclap_host> host> request_restart;
   Function<void,Pointer<const struct wclap_host> host> request_process;
   Function<void,Pointer<const struct wclap_host> host> request_callback;
};
typedef int64_t wclap_beattime;
typedef int64_t wclap_sectime;
typedef uint32_t wclap_id;
typedef int32_t wclap_note_expression;
struct wclap_event_header {
   uint32_t size;
   uint32_t time;
   uint16_t space_id;
   uint16_t type;
   uint32_t flags;
};
struct wclap_event_note {
   wclap_event_header_t header;

   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;
   double  velocity;
};
struct wclap_event_note_expression {
   wclap_event_header_t header;

   wclap_note_expression expression_id;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_value {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_mod {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double amount;
};
struct wclap_event_param_gesture {
   wclap_event_header_t header;
   wclap_id param_id;
};
struct wclap_event_transport {
   wclap_event_header_t header;

   uint32_t flags;

   wclap_beattime song_pos_beats;
   wclap_sectime  song_pos_seconds;

   double tempo;
   double tempo_inc;

   wclap_beattime loop_start_beats;
   wclap_beattime loop_end_beats;
   wclap_sectime  loop_start_seconds;
   wclap_sectime  loop_end_seconds;

   wclap_beattime bar_start;
   int32_t       bar_number;

   uint16_t tsig_num;
   uint16_t tsig_denom;
};
struct wclap_event_midi {
   wclap_event_header_t header;

   uint16_t port_index;
   uint8_t  data[3];
};
struct wclap_event_midi_sysex {
   wclap_event_header_t header;

   uint16_t       port_index;
   Pointer<const uint8_t> buffer;
   uint32_t       size;
};
struct wclap_event_midi2 {
   wclap_event_header_t header;

   uint16_t port_index;
   uint32_t data[4];
};
struct wclap_input_events {
   Pointer<void> ctx;
   Function<uint32_t,Pointer<const struct wclap_input_events> list> size;
   Function<Pointer<const wclap_event_header_t> ,Pointer<const struct wclap_input_events> list, uint32_t index> get;
};
struct wclap_output_events {
   Pointer<void> ctx;
   Function<bool,Pointer<const struct wclap_output_events> list,
                            Pointer<const wclap_event_header_t>       event> try_push;
};
struct wclap_audio_buffer {
   Pointer<Pointer<float>>  data32;
   Pointer<Pointer<double>> data64;
   uint32_t channel_count;
   uint32_t latency;
   uint64_t constant_mask;
};
typedef int32_t wclap_process_status;
struct wclap_process {
   int64_t steady_time;
   uint32_t frames_count;
   Pointer<const wclap_event_transport_t> transport;
   Pointer<const wclap_audio_buffer_t> audio_inputs;
   Pointer<wclap_audio_buffer_t>       audio_outputs;
   uint32_t                   audio_inputs_count;
   uint32_t                   audio_outputs_count;
   Pointer<const wclap_input_events_t>  in_events;
   Pointer<const wclap_output_events_t> out_events;
};
struct wclap_plugin_descriptor {
   wclap_version_t wclap_version;
   Pointer<const char> id;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> manual_url;
   Pointer<const char> support_url;
   Pointer<const char> version;
   Pointer<const char> description;
   Pointer<const char> Pointer<const> features;
};
struct wclap_plugin {
   Pointer<const wclap_plugin_descriptor_t> desc;

   Pointer<void> plugin_data;
   Function<bool,Pointer<const struct wclap_plugin> plugin> init;
   Function<void,Pointer<const struct wclap_plugin> plugin> destroy;
   Function<bool,Pointer<const struct wclap_plugin> plugin,
                            double                    sample_rate,
                            uint32_t                  min_frames_count,
                            uint32_t                  max_frames_count> activate;
   Function<void,Pointer<const struct wclap_plugin> plugin> deactivate;
   Function<bool,Pointer<const struct wclap_plugin> plugin> start_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> stop_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> reset;
   Function<wclap_process_status,Pointer<const struct wclap_plugin> plugin,
                                          Pointer<const wclap_process_t>     process> process;
   Function<Pointer<const void> ,Pointer<const struct wclap_plugin> plugin, Pointer<const char> id> get_extension;
   Function<void,Pointer<const struct wclap_plugin> plugin> on_main_thread;
};
struct wclap_note_name {
   char    name[CLAP_NAME_SIZE];
   int16_t port;
   int16_t key;
   int16_t channel;
};
struct wclap_plugin_note_name {
   Function<uint32_t,Pointer<const wclap_plugin_t> plugin> count;
   Function<bool,Pointer<const wclap_plugin_t> plugin, uint32_t index, Pointer<wclap_note_name_t> note_name> get;
};
struct wclap_host_note_name {
   Function<void,Pointer<const wclap_host_t> host> changed;
};
struct wclap_version {
   uint32_t major;
   uint32_t minor;
   uint32_t revision;
};
struct wclap_host {
   wclap_version_t wclap_version;

   Pointer<void> host_data;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> version;
   Function<Pointer<const void> ,Pointer<const struct wclap_host> host, Pointer<const char> extension_id> get_extension;
   Function<void,Pointer<const struct wclap_host> host> request_restart;
   Function<void,Pointer<const struct wclap_host> host> request_process;
   Function<void,Pointer<const struct wclap_host> host> request_callback;
};
typedef int64_t wclap_beattime;
typedef int64_t wclap_sectime;
typedef uint32_t wclap_id;
typedef int32_t wclap_note_expression;
struct wclap_event_header {
   uint32_t size;
   uint32_t time;
   uint16_t space_id;
   uint16_t type;
   uint32_t flags;
};
struct wclap_event_note {
   wclap_event_header_t header;

   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;
   double  velocity;
};
struct wclap_event_note_expression {
   wclap_event_header_t header;

   wclap_note_expression expression_id;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_value {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_mod {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double amount;
};
struct wclap_event_param_gesture {
   wclap_event_header_t header;
   wclap_id param_id;
};
struct wclap_event_transport {
   wclap_event_header_t header;

   uint32_t flags;

   wclap_beattime song_pos_beats;
   wclap_sectime  song_pos_seconds;

   double tempo;
   double tempo_inc;

   wclap_beattime loop_start_beats;
   wclap_beattime loop_end_beats;
   wclap_sectime  loop_start_seconds;
   wclap_sectime  loop_end_seconds;

   wclap_beattime bar_start;
   int32_t       bar_number;

   uint16_t tsig_num;
   uint16_t tsig_denom;
};
struct wclap_event_midi {
   wclap_event_header_t header;

   uint16_t port_index;
   uint8_t  data[3];
};
struct wclap_event_midi_sysex {
   wclap_event_header_t header;

   uint16_t       port_index;
   Pointer<const uint8_t> buffer;
   uint32_t       size;
};
struct wclap_event_midi2 {
   wclap_event_header_t header;

   uint16_t port_index;
   uint32_t data[4];
};
struct wclap_input_events {
   Pointer<void> ctx;
   Function<uint32_t,Pointer<const struct wclap_input_events> list> size;
   Function<Pointer<const wclap_event_header_t> ,Pointer<const struct wclap_input_events> list, uint32_t index> get;
};
struct wclap_output_events {
   Pointer<void> ctx;
   Function<bool,Pointer<const struct wclap_output_events> list,
                            Pointer<const wclap_event_header_t>       event> try_push;
};
struct wclap_audio_buffer {
   Pointer<Pointer<float>>  data32;
   Pointer<Pointer<double>> data64;
   uint32_t channel_count;
   uint32_t latency;
   uint64_t constant_mask;
};
typedef int32_t wclap_process_status;
struct wclap_process {
   int64_t steady_time;
   uint32_t frames_count;
   Pointer<const wclap_event_transport_t> transport;
   Pointer<const wclap_audio_buffer_t> audio_inputs;
   Pointer<wclap_audio_buffer_t>       audio_outputs;
   uint32_t                   audio_inputs_count;
   uint32_t                   audio_outputs_count;
   Pointer<const wclap_input_events_t>  in_events;
   Pointer<const wclap_output_events_t> out_events;
};
struct wclap_plugin_descriptor {
   wclap_version_t wclap_version;
   Pointer<const char> id;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> manual_url;
   Pointer<const char> support_url;
   Pointer<const char> version;
   Pointer<const char> description;
   Pointer<const char> Pointer<const> features;
};
struct wclap_plugin {
   Pointer<const wclap_plugin_descriptor_t> desc;

   Pointer<void> plugin_data;
   Function<bool,Pointer<const struct wclap_plugin> plugin> init;
   Function<void,Pointer<const struct wclap_plugin> plugin> destroy;
   Function<bool,Pointer<const struct wclap_plugin> plugin,
                            double                    sample_rate,
                            uint32_t                  min_frames_count,
                            uint32_t                  max_frames_count> activate;
   Function<void,Pointer<const struct wclap_plugin> plugin> deactivate;
   Function<bool,Pointer<const struct wclap_plugin> plugin> start_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> stop_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> reset;
   Function<wclap_process_status,Pointer<const struct wclap_plugin> plugin,
                                          Pointer<const wclap_process_t>     process> process;
   Function<Pointer<const void> ,Pointer<const struct wclap_plugin> plugin, Pointer<const char> id> get_extension;
   Function<void,Pointer<const struct wclap_plugin> plugin> on_main_thread;
};
struct wclap_note_port_info {
   wclap_id  id;
   uint32_t supported_dialects;
   uint32_t preferred_dialect;
   char     name[CLAP_NAME_SIZE];
};
struct wclap_plugin_note_ports {
   Function<uint32_t,Pointer<const wclap_plugin_t> plugin, bool is_input> count;
   Function<bool,Pointer<const wclap_plugin_t>   plugin,
                       uint32_t               index,
                       bool                   is_input,
                       Pointer<wclap_note_port_info_t> info> get;
};
struct wclap_host_note_ports {
   Function<uint32_t,Pointer<const wclap_host_t> host> supported_dialects;
   Function<void,Pointer<const wclap_host_t> host, uint32_t flags> rescan;
};
struct wclap_version {
   uint32_t major;
   uint32_t minor;
   uint32_t revision;
};
struct wclap_host {
   wclap_version_t wclap_version;

   Pointer<void> host_data;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> version;
   Function<Pointer<const void> ,Pointer<const struct wclap_host> host, Pointer<const char> extension_id> get_extension;
   Function<void,Pointer<const struct wclap_host> host> request_restart;
   Function<void,Pointer<const struct wclap_host> host> request_process;
   Function<void,Pointer<const struct wclap_host> host> request_callback;
};
typedef int64_t wclap_beattime;
typedef int64_t wclap_sectime;
typedef uint32_t wclap_id;
typedef int32_t wclap_note_expression;
struct wclap_event_header {
   uint32_t size;
   uint32_t time;
   uint16_t space_id;
   uint16_t type;
   uint32_t flags;
};
struct wclap_event_note {
   wclap_event_header_t header;

   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;
   double  velocity;
};
struct wclap_event_note_expression {
   wclap_event_header_t header;

   wclap_note_expression expression_id;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_value {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_mod {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double amount;
};
struct wclap_event_param_gesture {
   wclap_event_header_t header;
   wclap_id param_id;
};
struct wclap_event_transport {
   wclap_event_header_t header;

   uint32_t flags;

   wclap_beattime song_pos_beats;
   wclap_sectime  song_pos_seconds;

   double tempo;
   double tempo_inc;

   wclap_beattime loop_start_beats;
   wclap_beattime loop_end_beats;
   wclap_sectime  loop_start_seconds;
   wclap_sectime  loop_end_seconds;

   wclap_beattime bar_start;
   int32_t       bar_number;

   uint16_t tsig_num;
   uint16_t tsig_denom;
};
struct wclap_event_midi {
   wclap_event_header_t header;

   uint16_t port_index;
   uint8_t  data[3];
};
struct wclap_event_midi_sysex {
   wclap_event_header_t header;

   uint16_t       port_index;
   Pointer<const uint8_t> buffer;
   uint32_t       size;
};
struct wclap_event_midi2 {
   wclap_event_header_t header;

   uint16_t port_index;
   uint32_t data[4];
};
struct wclap_input_events {
   Pointer<void> ctx;
   Function<uint32_t,Pointer<const struct wclap_input_events> list> size;
   Function<Pointer<const wclap_event_header_t> ,Pointer<const struct wclap_input_events> list, uint32_t index> get;
};
struct wclap_output_events {
   Pointer<void> ctx;
   Function<bool,Pointer<const struct wclap_output_events> list,
                            Pointer<const wclap_event_header_t>       event> try_push;
};
struct wclap_audio_buffer {
   Pointer<Pointer<float>>  data32;
   Pointer<Pointer<double>> data64;
   uint32_t channel_count;
   uint32_t latency;
   uint64_t constant_mask;
};
typedef int32_t wclap_process_status;
struct wclap_process {
   int64_t steady_time;
   uint32_t frames_count;
   Pointer<const wclap_event_transport_t> transport;
   Pointer<const wclap_audio_buffer_t> audio_inputs;
   Pointer<wclap_audio_buffer_t>       audio_outputs;
   uint32_t                   audio_inputs_count;
   uint32_t                   audio_outputs_count;
   Pointer<const wclap_input_events_t>  in_events;
   Pointer<const wclap_output_events_t> out_events;
};
struct wclap_plugin_descriptor {
   wclap_version_t wclap_version;
   Pointer<const char> id;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> manual_url;
   Pointer<const char> support_url;
   Pointer<const char> version;
   Pointer<const char> description;
   Pointer<const char> Pointer<const> features;
};
struct wclap_plugin {
   Pointer<const wclap_plugin_descriptor_t> desc;

   Pointer<void> plugin_data;
   Function<bool,Pointer<const struct wclap_plugin> plugin> init;
   Function<void,Pointer<const struct wclap_plugin> plugin> destroy;
   Function<bool,Pointer<const struct wclap_plugin> plugin,
                            double                    sample_rate,
                            uint32_t                  min_frames_count,
                            uint32_t                  max_frames_count> activate;
   Function<void,Pointer<const struct wclap_plugin> plugin> deactivate;
   Function<bool,Pointer<const struct wclap_plugin> plugin> start_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> stop_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> reset;
   Function<wclap_process_status,Pointer<const struct wclap_plugin> plugin,
                                          Pointer<const wclap_process_t>     process> process;
   Function<Pointer<const void> ,Pointer<const struct wclap_plugin> plugin, Pointer<const char> id> get_extension;
   Function<void,Pointer<const struct wclap_plugin> plugin> on_main_thread;
};
typedef uint32_t wclap_param_info_flags;
typedef uint32_t wclap_param_rescan_flags;
typedef uint32_t wclap_param_clear_flags;
struct wclap_param_info {
   wclap_id id;

   wclap_param_info_flags flags;
   Pointer<void> cookie;
   char name[CLAP_NAME_SIZE];
   char module[CLAP_PATH_SIZE];

   double min_value;
   double max_value;
   double default_value;
};
struct wclap_plugin_params {
   Function<uint32_t,Pointer<const wclap_plugin_t> plugin> count;
   Function<bool,Pointer<const wclap_plugin_t> plugin,
                            uint32_t             param_index,
                            Pointer<wclap_param_info_t>   param_info> get_info;
   Function<bool,Pointer<const wclap_plugin_t> plugin, wclap_id param_id, Pointer<double> out_value> get_value;
   Function<bool,Pointer<const wclap_plugin_t> plugin,
                                 wclap_id              param_id,
                                 double               value,
                                 Pointer<char>                out_buffer,
                                 uint32_t             out_buffer_capacity> value_to_text;
   Function<bool,Pointer<const wclap_plugin_t> plugin,
                                 wclap_id              param_id,
                                 Pointer<const char>          param_value_text,
                                 Pointer<double>              out_value> text_to_value;
   Function<void,Pointer<const wclap_plugin_t>        plugin,
                         Pointer<const wclap_input_events_t>  in,
                         Pointer<const wclap_output_events_t> out> flush;
};
struct wclap_host_params {
   Function<void,Pointer<const wclap_host_t> host, wclap_param_rescan_flags flags> rescan;
   Function<void,Pointer<const wclap_host_t> host, wclap_id param_id, wclap_param_clear_flags flags> clear;
   Function<void,Pointer<const wclap_host_t> host> request_flush;
};
struct wclap_color {
   uint8_t alpha;
   uint8_t red;
   uint8_t green;
   uint8_t blue;
};
struct wclap_plugin_param_indication {
   Function<void,Pointer<const wclap_plugin_t> plugin,
                               wclap_id              param_id,
                               bool                 has_mapping,
                               Pointer<const wclap_color_t>  color,
                               Pointer<const char>          label,
                               Pointer<const char>          description> set_mapping;
   Function<void,Pointer<const wclap_plugin_t> plugin,
                                  wclap_id              param_id,
                                  uint32_t             automation_state,
                                  Pointer<const wclap_color_t>  color> set_automation;
};
struct wclap_version {
   uint32_t major;
   uint32_t minor;
   uint32_t revision;
};
struct wclap_host {
   wclap_version_t wclap_version;

   Pointer<void> host_data;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> version;
   Function<Pointer<const void> ,Pointer<const struct wclap_host> host, Pointer<const char> extension_id> get_extension;
   Function<void,Pointer<const struct wclap_host> host> request_restart;
   Function<void,Pointer<const struct wclap_host> host> request_process;
   Function<void,Pointer<const struct wclap_host> host> request_callback;
};
typedef int64_t wclap_beattime;
typedef int64_t wclap_sectime;
typedef uint32_t wclap_id;
typedef int32_t wclap_note_expression;
struct wclap_event_header {
   uint32_t size;
   uint32_t time;
   uint16_t space_id;
   uint16_t type;
   uint32_t flags;
};
struct wclap_event_note {
   wclap_event_header_t header;

   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;
   double  velocity;
};
struct wclap_event_note_expression {
   wclap_event_header_t header;

   wclap_note_expression expression_id;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_value {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_mod {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double amount;
};
struct wclap_event_param_gesture {
   wclap_event_header_t header;
   wclap_id param_id;
};
struct wclap_event_transport {
   wclap_event_header_t header;

   uint32_t flags;

   wclap_beattime song_pos_beats;
   wclap_sectime  song_pos_seconds;

   double tempo;
   double tempo_inc;

   wclap_beattime loop_start_beats;
   wclap_beattime loop_end_beats;
   wclap_sectime  loop_start_seconds;
   wclap_sectime  loop_end_seconds;

   wclap_beattime bar_start;
   int32_t       bar_number;

   uint16_t tsig_num;
   uint16_t tsig_denom;
};
struct wclap_event_midi {
   wclap_event_header_t header;

   uint16_t port_index;
   uint8_t  data[3];
};
struct wclap_event_midi_sysex {
   wclap_event_header_t header;

   uint16_t       port_index;
   Pointer<const uint8_t> buffer;
   uint32_t       size;
};
struct wclap_event_midi2 {
   wclap_event_header_t header;

   uint16_t port_index;
   uint32_t data[4];
};
struct wclap_input_events {
   Pointer<void> ctx;
   Function<uint32_t,Pointer<const struct wclap_input_events> list> size;
   Function<Pointer<const wclap_event_header_t> ,Pointer<const struct wclap_input_events> list, uint32_t index> get;
};
struct wclap_output_events {
   Pointer<void> ctx;
   Function<bool,Pointer<const struct wclap_output_events> list,
                            Pointer<const wclap_event_header_t>       event> try_push;
};
struct wclap_audio_buffer {
   Pointer<Pointer<float>>  data32;
   Pointer<Pointer<double>> data64;
   uint32_t channel_count;
   uint32_t latency;
   uint64_t constant_mask;
};
typedef int32_t wclap_process_status;
struct wclap_process {
   int64_t steady_time;
   uint32_t frames_count;
   Pointer<const wclap_event_transport_t> transport;
   Pointer<const wclap_audio_buffer_t> audio_inputs;
   Pointer<wclap_audio_buffer_t>       audio_outputs;
   uint32_t                   audio_inputs_count;
   uint32_t                   audio_outputs_count;
   Pointer<const wclap_input_events_t>  in_events;
   Pointer<const wclap_output_events_t> out_events;
};
struct wclap_plugin_descriptor {
   wclap_version_t wclap_version;
   Pointer<const char> id;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> manual_url;
   Pointer<const char> support_url;
   Pointer<const char> version;
   Pointer<const char> description;
   Pointer<const char> Pointer<const> features;
};
struct wclap_plugin {
   Pointer<const wclap_plugin_descriptor_t> desc;

   Pointer<void> plugin_data;
   Function<bool,Pointer<const struct wclap_plugin> plugin> init;
   Function<void,Pointer<const struct wclap_plugin> plugin> destroy;
   Function<bool,Pointer<const struct wclap_plugin> plugin,
                            double                    sample_rate,
                            uint32_t                  min_frames_count,
                            uint32_t                  max_frames_count> activate;
   Function<void,Pointer<const struct wclap_plugin> plugin> deactivate;
   Function<bool,Pointer<const struct wclap_plugin> plugin> start_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> stop_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> reset;
   Function<wclap_process_status,Pointer<const struct wclap_plugin> plugin,
                                          Pointer<const wclap_process_t>     process> process;
   Function<Pointer<const void> ,Pointer<const struct wclap_plugin> plugin, Pointer<const char> id> get_extension;
   Function<void,Pointer<const struct wclap_plugin> plugin> on_main_thread;
};
typedef uint32_t wclap_param_info_flags;
typedef uint32_t wclap_param_rescan_flags;
typedef uint32_t wclap_param_clear_flags;
struct wclap_param_info {
   wclap_id id;

   wclap_param_info_flags flags;
   Pointer<void> cookie;
   char name[CLAP_NAME_SIZE];
   char module[CLAP_PATH_SIZE];

   double min_value;
   double max_value;
   double default_value;
};
struct wclap_plugin_params {
   Function<uint32_t,Pointer<const wclap_plugin_t> plugin> count;
   Function<bool,Pointer<const wclap_plugin_t> plugin,
                            uint32_t             param_index,
                            Pointer<wclap_param_info_t>   param_info> get_info;
   Function<bool,Pointer<const wclap_plugin_t> plugin, wclap_id param_id, Pointer<double> out_value> get_value;
   Function<bool,Pointer<const wclap_plugin_t> plugin,
                                 wclap_id              param_id,
                                 double               value,
                                 Pointer<char>                out_buffer,
                                 uint32_t             out_buffer_capacity> value_to_text;
   Function<bool,Pointer<const wclap_plugin_t> plugin,
                                 wclap_id              param_id,
                                 Pointer<const char>          param_value_text,
                                 Pointer<double>              out_value> text_to_value;
   Function<void,Pointer<const wclap_plugin_t>        plugin,
                         Pointer<const wclap_input_events_t>  in,
                         Pointer<const wclap_output_events_t> out> flush;
};
struct wclap_host_params {
   Function<void,Pointer<const wclap_host_t> host, wclap_param_rescan_flags flags> rescan;
   Function<void,Pointer<const wclap_host_t> host, wclap_id param_id, wclap_param_clear_flags flags> clear;
   Function<void,Pointer<const wclap_host_t> host> request_flush;
};
struct wclap_version {
   uint32_t major;
   uint32_t minor;
   uint32_t revision;
};
struct wclap_host {
   wclap_version_t wclap_version;

   Pointer<void> host_data;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> version;
   Function<Pointer<const void> ,Pointer<const struct wclap_host> host, Pointer<const char> extension_id> get_extension;
   Function<void,Pointer<const struct wclap_host> host> request_restart;
   Function<void,Pointer<const struct wclap_host> host> request_process;
   Function<void,Pointer<const struct wclap_host> host> request_callback;
};
typedef int64_t wclap_beattime;
typedef int64_t wclap_sectime;
typedef uint32_t wclap_id;
typedef int32_t wclap_note_expression;
struct wclap_event_header {
   uint32_t size;
   uint32_t time;
   uint16_t space_id;
   uint16_t type;
   uint32_t flags;
};
struct wclap_event_note {
   wclap_event_header_t header;

   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;
   double  velocity;
};
struct wclap_event_note_expression {
   wclap_event_header_t header;

   wclap_note_expression expression_id;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_value {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_mod {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double amount;
};
struct wclap_event_param_gesture {
   wclap_event_header_t header;
   wclap_id param_id;
};
struct wclap_event_transport {
   wclap_event_header_t header;

   uint32_t flags;

   wclap_beattime song_pos_beats;
   wclap_sectime  song_pos_seconds;

   double tempo;
   double tempo_inc;

   wclap_beattime loop_start_beats;
   wclap_beattime loop_end_beats;
   wclap_sectime  loop_start_seconds;
   wclap_sectime  loop_end_seconds;

   wclap_beattime bar_start;
   int32_t       bar_number;

   uint16_t tsig_num;
   uint16_t tsig_denom;
};
struct wclap_event_midi {
   wclap_event_header_t header;

   uint16_t port_index;
   uint8_t  data[3];
};
struct wclap_event_midi_sysex {
   wclap_event_header_t header;

   uint16_t       port_index;
   Pointer<const uint8_t> buffer;
   uint32_t       size;
};
struct wclap_event_midi2 {
   wclap_event_header_t header;

   uint16_t port_index;
   uint32_t data[4];
};
struct wclap_input_events {
   Pointer<void> ctx;
   Function<uint32_t,Pointer<const struct wclap_input_events> list> size;
   Function<Pointer<const wclap_event_header_t> ,Pointer<const struct wclap_input_events> list, uint32_t index> get;
};
struct wclap_output_events {
   Pointer<void> ctx;
   Function<bool,Pointer<const struct wclap_output_events> list,
                            Pointer<const wclap_event_header_t>       event> try_push;
};
struct wclap_audio_buffer {
   Pointer<Pointer<float>>  data32;
   Pointer<Pointer<double>> data64;
   uint32_t channel_count;
   uint32_t latency;
   uint64_t constant_mask;
};
typedef int32_t wclap_process_status;
struct wclap_process {
   int64_t steady_time;
   uint32_t frames_count;
   Pointer<const wclap_event_transport_t> transport;
   Pointer<const wclap_audio_buffer_t> audio_inputs;
   Pointer<wclap_audio_buffer_t>       audio_outputs;
   uint32_t                   audio_inputs_count;
   uint32_t                   audio_outputs_count;
   Pointer<const wclap_input_events_t>  in_events;
   Pointer<const wclap_output_events_t> out_events;
};
struct wclap_plugin_descriptor {
   wclap_version_t wclap_version;
   Pointer<const char> id;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> manual_url;
   Pointer<const char> support_url;
   Pointer<const char> version;
   Pointer<const char> description;
   Pointer<const char> Pointer<const> features;
};
struct wclap_plugin {
   Pointer<const wclap_plugin_descriptor_t> desc;

   Pointer<void> plugin_data;
   Function<bool,Pointer<const struct wclap_plugin> plugin> init;
   Function<void,Pointer<const struct wclap_plugin> plugin> destroy;
   Function<bool,Pointer<const struct wclap_plugin> plugin,
                            double                    sample_rate,
                            uint32_t                  min_frames_count,
                            uint32_t                  max_frames_count> activate;
   Function<void,Pointer<const struct wclap_plugin> plugin> deactivate;
   Function<bool,Pointer<const struct wclap_plugin> plugin> start_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> stop_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> reset;
   Function<wclap_process_status,Pointer<const struct wclap_plugin> plugin,
                                          Pointer<const wclap_process_t>     process> process;
   Function<Pointer<const void> ,Pointer<const struct wclap_plugin> plugin, Pointer<const char> id> get_extension;
   Function<void,Pointer<const struct wclap_plugin> plugin> on_main_thread;
};
typedef uint32_t wclap_posix_fd_flags_t;
struct wclap_plugin_posix_fd_support {
   Function<void,Pointer<const wclap_plugin_t> plugin, int fd, wclap_posix_fd_flags_t flags> on_fd;
};
struct wclap_host_posix_fd_support {
   Function<bool,Pointer<const wclap_host_t> host, int fd, wclap_posix_fd_flags_t flags> register_fd;
   Function<bool,Pointer<const wclap_host_t> host, int fd, wclap_posix_fd_flags_t flags> modify_fd;
   Function<bool,Pointer<const wclap_host_t> host, int fd> unregister_fd;
};
struct wclap_version {
   uint32_t major;
   uint32_t minor;
   uint32_t revision;
};
struct wclap_host {
   wclap_version_t wclap_version;

   Pointer<void> host_data;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> version;
   Function<Pointer<const void> ,Pointer<const struct wclap_host> host, Pointer<const char> extension_id> get_extension;
   Function<void,Pointer<const struct wclap_host> host> request_restart;
   Function<void,Pointer<const struct wclap_host> host> request_process;
   Function<void,Pointer<const struct wclap_host> host> request_callback;
};
typedef int64_t wclap_beattime;
typedef int64_t wclap_sectime;
typedef uint32_t wclap_id;
typedef int32_t wclap_note_expression;
struct wclap_event_header {
   uint32_t size;
   uint32_t time;
   uint16_t space_id;
   uint16_t type;
   uint32_t flags;
};
struct wclap_event_note {
   wclap_event_header_t header;

   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;
   double  velocity;
};
struct wclap_event_note_expression {
   wclap_event_header_t header;

   wclap_note_expression expression_id;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_value {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_mod {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double amount;
};
struct wclap_event_param_gesture {
   wclap_event_header_t header;
   wclap_id param_id;
};
struct wclap_event_transport {
   wclap_event_header_t header;

   uint32_t flags;

   wclap_beattime song_pos_beats;
   wclap_sectime  song_pos_seconds;

   double tempo;
   double tempo_inc;

   wclap_beattime loop_start_beats;
   wclap_beattime loop_end_beats;
   wclap_sectime  loop_start_seconds;
   wclap_sectime  loop_end_seconds;

   wclap_beattime bar_start;
   int32_t       bar_number;

   uint16_t tsig_num;
   uint16_t tsig_denom;
};
struct wclap_event_midi {
   wclap_event_header_t header;

   uint16_t port_index;
   uint8_t  data[3];
};
struct wclap_event_midi_sysex {
   wclap_event_header_t header;

   uint16_t       port_index;
   Pointer<const uint8_t> buffer;
   uint32_t       size;
};
struct wclap_event_midi2 {
   wclap_event_header_t header;

   uint16_t port_index;
   uint32_t data[4];
};
struct wclap_input_events {
   Pointer<void> ctx;
   Function<uint32_t,Pointer<const struct wclap_input_events> list> size;
   Function<Pointer<const wclap_event_header_t> ,Pointer<const struct wclap_input_events> list, uint32_t index> get;
};
struct wclap_output_events {
   Pointer<void> ctx;
   Function<bool,Pointer<const struct wclap_output_events> list,
                            Pointer<const wclap_event_header_t>       event> try_push;
};
struct wclap_audio_buffer {
   Pointer<Pointer<float>>  data32;
   Pointer<Pointer<double>> data64;
   uint32_t channel_count;
   uint32_t latency;
   uint64_t constant_mask;
};
typedef int32_t wclap_process_status;
struct wclap_process {
   int64_t steady_time;
   uint32_t frames_count;
   Pointer<const wclap_event_transport_t> transport;
   Pointer<const wclap_audio_buffer_t> audio_inputs;
   Pointer<wclap_audio_buffer_t>       audio_outputs;
   uint32_t                   audio_inputs_count;
   uint32_t                   audio_outputs_count;
   Pointer<const wclap_input_events_t>  in_events;
   Pointer<const wclap_output_events_t> out_events;
};
struct wclap_plugin_descriptor {
   wclap_version_t wclap_version;
   Pointer<const char> id;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> manual_url;
   Pointer<const char> support_url;
   Pointer<const char> version;
   Pointer<const char> description;
   Pointer<const char> Pointer<const> features;
};
struct wclap_plugin {
   Pointer<const wclap_plugin_descriptor_t> desc;

   Pointer<void> plugin_data;
   Function<bool,Pointer<const struct wclap_plugin> plugin> init;
   Function<void,Pointer<const struct wclap_plugin> plugin> destroy;
   Function<bool,Pointer<const struct wclap_plugin> plugin,
                            double                    sample_rate,
                            uint32_t                  min_frames_count,
                            uint32_t                  max_frames_count> activate;
   Function<void,Pointer<const struct wclap_plugin> plugin> deactivate;
   Function<bool,Pointer<const struct wclap_plugin> plugin> start_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> stop_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> reset;
   Function<wclap_process_status,Pointer<const struct wclap_plugin> plugin,
                                          Pointer<const wclap_process_t>     process> process;
   Function<Pointer<const void> ,Pointer<const struct wclap_plugin> plugin, Pointer<const char> id> get_extension;
   Function<void,Pointer<const struct wclap_plugin> plugin> on_main_thread;
};
struct wclap_plugin_preset_load {
   Function<bool,Pointer<const wclap_plugin_t> plugin,
                                 uint32_t             location_kind,
                                 Pointer<const char>          location,
                                 Pointer<const char>          load_key> from_location;
};
struct wclap_host_preset_load {
   Function<void,Pointer<const wclap_host_t> host,
                            uint32_t           location_kind,
                            Pointer<const char>        location,
                            Pointer<const char>        load_key,
                            int32_t            os_error,
                            Pointer<const char>        msg> on_error;
   Function<void,Pointer<const wclap_host_t> host,
                          uint32_t           location_kind,
                          Pointer<const char>        location,
                          Pointer<const char>        load_key> loaded;
};
struct wclap_version {
   uint32_t major;
   uint32_t minor;
   uint32_t revision;
};
struct wclap_host {
   wclap_version_t wclap_version;

   Pointer<void> host_data;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> version;
   Function<Pointer<const void> ,Pointer<const struct wclap_host> host, Pointer<const char> extension_id> get_extension;
   Function<void,Pointer<const struct wclap_host> host> request_restart;
   Function<void,Pointer<const struct wclap_host> host> request_process;
   Function<void,Pointer<const struct wclap_host> host> request_callback;
};
typedef int64_t wclap_beattime;
typedef int64_t wclap_sectime;
typedef uint32_t wclap_id;
typedef int32_t wclap_note_expression;
struct wclap_event_header {
   uint32_t size;
   uint32_t time;
   uint16_t space_id;
   uint16_t type;
   uint32_t flags;
};
struct wclap_event_note {
   wclap_event_header_t header;

   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;
   double  velocity;
};
struct wclap_event_note_expression {
   wclap_event_header_t header;

   wclap_note_expression expression_id;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_value {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_mod {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double amount;
};
struct wclap_event_param_gesture {
   wclap_event_header_t header;
   wclap_id param_id;
};
struct wclap_event_transport {
   wclap_event_header_t header;

   uint32_t flags;

   wclap_beattime song_pos_beats;
   wclap_sectime  song_pos_seconds;

   double tempo;
   double tempo_inc;

   wclap_beattime loop_start_beats;
   wclap_beattime loop_end_beats;
   wclap_sectime  loop_start_seconds;
   wclap_sectime  loop_end_seconds;

   wclap_beattime bar_start;
   int32_t       bar_number;

   uint16_t tsig_num;
   uint16_t tsig_denom;
};
struct wclap_event_midi {
   wclap_event_header_t header;

   uint16_t port_index;
   uint8_t  data[3];
};
struct wclap_event_midi_sysex {
   wclap_event_header_t header;

   uint16_t       port_index;
   Pointer<const uint8_t> buffer;
   uint32_t       size;
};
struct wclap_event_midi2 {
   wclap_event_header_t header;

   uint16_t port_index;
   uint32_t data[4];
};
struct wclap_input_events {
   Pointer<void> ctx;
   Function<uint32_t,Pointer<const struct wclap_input_events> list> size;
   Function<Pointer<const wclap_event_header_t> ,Pointer<const struct wclap_input_events> list, uint32_t index> get;
};
struct wclap_output_events {
   Pointer<void> ctx;
   Function<bool,Pointer<const struct wclap_output_events> list,
                            Pointer<const wclap_event_header_t>       event> try_push;
};
struct wclap_audio_buffer {
   Pointer<Pointer<float>>  data32;
   Pointer<Pointer<double>> data64;
   uint32_t channel_count;
   uint32_t latency;
   uint64_t constant_mask;
};
typedef int32_t wclap_process_status;
struct wclap_process {
   int64_t steady_time;
   uint32_t frames_count;
   Pointer<const wclap_event_transport_t> transport;
   Pointer<const wclap_audio_buffer_t> audio_inputs;
   Pointer<wclap_audio_buffer_t>       audio_outputs;
   uint32_t                   audio_inputs_count;
   uint32_t                   audio_outputs_count;
   Pointer<const wclap_input_events_t>  in_events;
   Pointer<const wclap_output_events_t> out_events;
};
struct wclap_plugin_descriptor {
   wclap_version_t wclap_version;
   Pointer<const char> id;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> manual_url;
   Pointer<const char> support_url;
   Pointer<const char> version;
   Pointer<const char> description;
   Pointer<const char> Pointer<const> features;
};
struct wclap_plugin {
   Pointer<const wclap_plugin_descriptor_t> desc;

   Pointer<void> plugin_data;
   Function<bool,Pointer<const struct wclap_plugin> plugin> init;
   Function<void,Pointer<const struct wclap_plugin> plugin> destroy;
   Function<bool,Pointer<const struct wclap_plugin> plugin,
                            double                    sample_rate,
                            uint32_t                  min_frames_count,
                            uint32_t                  max_frames_count> activate;
   Function<void,Pointer<const struct wclap_plugin> plugin> deactivate;
   Function<bool,Pointer<const struct wclap_plugin> plugin> start_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> stop_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> reset;
   Function<wclap_process_status,Pointer<const struct wclap_plugin> plugin,
                                          Pointer<const wclap_process_t>     process> process;
   Function<Pointer<const void> ,Pointer<const struct wclap_plugin> plugin, Pointer<const char> id> get_extension;
   Function<void,Pointer<const struct wclap_plugin> plugin> on_main_thread;
};
struct wclap_remote_controls_page {
   char    section_name[CLAP_NAME_SIZE];
   wclap_id page_id;
   char    page_name[CLAP_NAME_SIZE];
   wclap_id param_ids[CLAP_REMOTE_CONTROLS_COUNT];
   bool is_for_preset;
};
struct wclap_plugin_remote_controls {
   Function<uint32_t,Pointer<const wclap_plugin_t> plugin> count;
   Function<bool,Pointer<const wclap_plugin_t>         plugin,
                       uint32_t                     page_index,
                       Pointer<wclap_remote_controls_page_t> page> get;
};
struct wclap_host_remote_controls {
   Function<void,Pointer<const wclap_host_t> host> changed;
   Function<void,Pointer<const wclap_host_t> host, wclap_id page_id> suggest_page;
};
struct wclap_version {
   uint32_t major;
   uint32_t minor;
   uint32_t revision;
};
struct wclap_host {
   wclap_version_t wclap_version;

   Pointer<void> host_data;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> version;
   Function<Pointer<const void> ,Pointer<const struct wclap_host> host, Pointer<const char> extension_id> get_extension;
   Function<void,Pointer<const struct wclap_host> host> request_restart;
   Function<void,Pointer<const struct wclap_host> host> request_process;
   Function<void,Pointer<const struct wclap_host> host> request_callback;
};
typedef int64_t wclap_beattime;
typedef int64_t wclap_sectime;
typedef uint32_t wclap_id;
typedef int32_t wclap_note_expression;
struct wclap_event_header {
   uint32_t size;
   uint32_t time;
   uint16_t space_id;
   uint16_t type;
   uint32_t flags;
};
struct wclap_event_note {
   wclap_event_header_t header;

   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;
   double  velocity;
};
struct wclap_event_note_expression {
   wclap_event_header_t header;

   wclap_note_expression expression_id;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_value {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_mod {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double amount;
};
struct wclap_event_param_gesture {
   wclap_event_header_t header;
   wclap_id param_id;
};
struct wclap_event_transport {
   wclap_event_header_t header;

   uint32_t flags;

   wclap_beattime song_pos_beats;
   wclap_sectime  song_pos_seconds;

   double tempo;
   double tempo_inc;

   wclap_beattime loop_start_beats;
   wclap_beattime loop_end_beats;
   wclap_sectime  loop_start_seconds;
   wclap_sectime  loop_end_seconds;

   wclap_beattime bar_start;
   int32_t       bar_number;

   uint16_t tsig_num;
   uint16_t tsig_denom;
};
struct wclap_event_midi {
   wclap_event_header_t header;

   uint16_t port_index;
   uint8_t  data[3];
};
struct wclap_event_midi_sysex {
   wclap_event_header_t header;

   uint16_t       port_index;
   Pointer<const uint8_t> buffer;
   uint32_t       size;
};
struct wclap_event_midi2 {
   wclap_event_header_t header;

   uint16_t port_index;
   uint32_t data[4];
};
struct wclap_input_events {
   Pointer<void> ctx;
   Function<uint32_t,Pointer<const struct wclap_input_events> list> size;
   Function<Pointer<const wclap_event_header_t> ,Pointer<const struct wclap_input_events> list, uint32_t index> get;
};
struct wclap_output_events {
   Pointer<void> ctx;
   Function<bool,Pointer<const struct wclap_output_events> list,
                            Pointer<const wclap_event_header_t>       event> try_push;
};
struct wclap_audio_buffer {
   Pointer<Pointer<float>>  data32;
   Pointer<Pointer<double>> data64;
   uint32_t channel_count;
   uint32_t latency;
   uint64_t constant_mask;
};
typedef int32_t wclap_process_status;
struct wclap_process {
   int64_t steady_time;
   uint32_t frames_count;
   Pointer<const wclap_event_transport_t> transport;
   Pointer<const wclap_audio_buffer_t> audio_inputs;
   Pointer<wclap_audio_buffer_t>       audio_outputs;
   uint32_t                   audio_inputs_count;
   uint32_t                   audio_outputs_count;
   Pointer<const wclap_input_events_t>  in_events;
   Pointer<const wclap_output_events_t> out_events;
};
struct wclap_plugin_descriptor {
   wclap_version_t wclap_version;
   Pointer<const char> id;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> manual_url;
   Pointer<const char> support_url;
   Pointer<const char> version;
   Pointer<const char> description;
   Pointer<const char> Pointer<const> features;
};
struct wclap_plugin {
   Pointer<const wclap_plugin_descriptor_t> desc;

   Pointer<void> plugin_data;
   Function<bool,Pointer<const struct wclap_plugin> plugin> init;
   Function<void,Pointer<const struct wclap_plugin> plugin> destroy;
   Function<bool,Pointer<const struct wclap_plugin> plugin,
                            double                    sample_rate,
                            uint32_t                  min_frames_count,
                            uint32_t                  max_frames_count> activate;
   Function<void,Pointer<const struct wclap_plugin> plugin> deactivate;
   Function<bool,Pointer<const struct wclap_plugin> plugin> start_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> stop_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> reset;
   Function<wclap_process_status,Pointer<const struct wclap_plugin> plugin,
                                          Pointer<const wclap_process_t>     process> process;
   Function<Pointer<const void> ,Pointer<const struct wclap_plugin> plugin, Pointer<const char> id> get_extension;
   Function<void,Pointer<const struct wclap_plugin> plugin> on_main_thread;
};
typedef int32_t wclap_plugin_render_mode;
struct wclap_plugin_render {
   Function<bool,Pointer<const wclap_plugin_t> plugin> has_hard_realtime_requirement;
   Function<bool,Pointer<const wclap_plugin_t> plugin, wclap_plugin_render_mode mode> set;
};
struct wclap_version {
   uint32_t major;
   uint32_t minor;
   uint32_t revision;
};
struct wclap_host {
   wclap_version_t wclap_version;

   Pointer<void> host_data;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> version;
   Function<Pointer<const void> ,Pointer<const struct wclap_host> host, Pointer<const char> extension_id> get_extension;
   Function<void,Pointer<const struct wclap_host> host> request_restart;
   Function<void,Pointer<const struct wclap_host> host> request_process;
   Function<void,Pointer<const struct wclap_host> host> request_callback;
};
typedef int64_t wclap_beattime;
typedef int64_t wclap_sectime;
typedef uint32_t wclap_id;
typedef int32_t wclap_note_expression;
struct wclap_event_header {
   uint32_t size;
   uint32_t time;
   uint16_t space_id;
   uint16_t type;
   uint32_t flags;
};
struct wclap_event_note {
   wclap_event_header_t header;

   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;
   double  velocity;
};
struct wclap_event_note_expression {
   wclap_event_header_t header;

   wclap_note_expression expression_id;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_value {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_mod {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double amount;
};
struct wclap_event_param_gesture {
   wclap_event_header_t header;
   wclap_id param_id;
};
struct wclap_event_transport {
   wclap_event_header_t header;

   uint32_t flags;

   wclap_beattime song_pos_beats;
   wclap_sectime  song_pos_seconds;

   double tempo;
   double tempo_inc;

   wclap_beattime loop_start_beats;
   wclap_beattime loop_end_beats;
   wclap_sectime  loop_start_seconds;
   wclap_sectime  loop_end_seconds;

   wclap_beattime bar_start;
   int32_t       bar_number;

   uint16_t tsig_num;
   uint16_t tsig_denom;
};
struct wclap_event_midi {
   wclap_event_header_t header;

   uint16_t port_index;
   uint8_t  data[3];
};
struct wclap_event_midi_sysex {
   wclap_event_header_t header;

   uint16_t       port_index;
   Pointer<const uint8_t> buffer;
   uint32_t       size;
};
struct wclap_event_midi2 {
   wclap_event_header_t header;

   uint16_t port_index;
   uint32_t data[4];
};
struct wclap_input_events {
   Pointer<void> ctx;
   Function<uint32_t,Pointer<const struct wclap_input_events> list> size;
   Function<Pointer<const wclap_event_header_t> ,Pointer<const struct wclap_input_events> list, uint32_t index> get;
};
struct wclap_output_events {
   Pointer<void> ctx;
   Function<bool,Pointer<const struct wclap_output_events> list,
                            Pointer<const wclap_event_header_t>       event> try_push;
};
struct wclap_audio_buffer {
   Pointer<Pointer<float>>  data32;
   Pointer<Pointer<double>> data64;
   uint32_t channel_count;
   uint32_t latency;
   uint64_t constant_mask;
};
typedef int32_t wclap_process_status;
struct wclap_process {
   int64_t steady_time;
   uint32_t frames_count;
   Pointer<const wclap_event_transport_t> transport;
   Pointer<const wclap_audio_buffer_t> audio_inputs;
   Pointer<wclap_audio_buffer_t>       audio_outputs;
   uint32_t                   audio_inputs_count;
   uint32_t                   audio_outputs_count;
   Pointer<const wclap_input_events_t>  in_events;
   Pointer<const wclap_output_events_t> out_events;
};
struct wclap_plugin_descriptor {
   wclap_version_t wclap_version;
   Pointer<const char> id;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> manual_url;
   Pointer<const char> support_url;
   Pointer<const char> version;
   Pointer<const char> description;
   Pointer<const char> Pointer<const> features;
};
struct wclap_plugin {
   Pointer<const wclap_plugin_descriptor_t> desc;

   Pointer<void> plugin_data;
   Function<bool,Pointer<const struct wclap_plugin> plugin> init;
   Function<void,Pointer<const struct wclap_plugin> plugin> destroy;
   Function<bool,Pointer<const struct wclap_plugin> plugin,
                            double                    sample_rate,
                            uint32_t                  min_frames_count,
                            uint32_t                  max_frames_count> activate;
   Function<void,Pointer<const struct wclap_plugin> plugin> deactivate;
   Function<bool,Pointer<const struct wclap_plugin> plugin> start_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> stop_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> reset;
   Function<wclap_process_status,Pointer<const struct wclap_plugin> plugin,
                                          Pointer<const wclap_process_t>     process> process;
   Function<Pointer<const void> ,Pointer<const struct wclap_plugin> plugin, Pointer<const char> id> get_extension;
   Function<void,Pointer<const struct wclap_plugin> plugin> on_main_thread;
};
struct wclap_istream {
   Pointer<void> ctx;
   Function<int64_t,Pointer<const struct wclap_istream> stream, Pointer<void> buffer, uint64_t size> read;
};
struct wclap_ostream {
   Pointer<void> ctx;
   Function<int64_t,Pointer<const struct wclap_ostream> stream, Pointer<const void> buffer, uint64_t size> write;
};
struct wclap_plugin_state_context {
   Function<bool,Pointer<const wclap_plugin_t>  plugin,
                        Pointer<const wclap_ostream_t> stream,
                        uint32_t              context_type> save;
   Function<bool,Pointer<const wclap_plugin_t>  plugin,
                        Pointer<const wclap_istream_t> stream,
                        uint32_t              context_type> load;
};
struct wclap_version {
   uint32_t major;
   uint32_t minor;
   uint32_t revision;
};
struct wclap_host {
   wclap_version_t wclap_version;

   Pointer<void> host_data;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> version;
   Function<Pointer<const void> ,Pointer<const struct wclap_host> host, Pointer<const char> extension_id> get_extension;
   Function<void,Pointer<const struct wclap_host> host> request_restart;
   Function<void,Pointer<const struct wclap_host> host> request_process;
   Function<void,Pointer<const struct wclap_host> host> request_callback;
};
typedef int64_t wclap_beattime;
typedef int64_t wclap_sectime;
typedef uint32_t wclap_id;
typedef int32_t wclap_note_expression;
struct wclap_event_header {
   uint32_t size;
   uint32_t time;
   uint16_t space_id;
   uint16_t type;
   uint32_t flags;
};
struct wclap_event_note {
   wclap_event_header_t header;

   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;
   double  velocity;
};
struct wclap_event_note_expression {
   wclap_event_header_t header;

   wclap_note_expression expression_id;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_value {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_mod {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double amount;
};
struct wclap_event_param_gesture {
   wclap_event_header_t header;
   wclap_id param_id;
};
struct wclap_event_transport {
   wclap_event_header_t header;

   uint32_t flags;

   wclap_beattime song_pos_beats;
   wclap_sectime  song_pos_seconds;

   double tempo;
   double tempo_inc;

   wclap_beattime loop_start_beats;
   wclap_beattime loop_end_beats;
   wclap_sectime  loop_start_seconds;
   wclap_sectime  loop_end_seconds;

   wclap_beattime bar_start;
   int32_t       bar_number;

   uint16_t tsig_num;
   uint16_t tsig_denom;
};
struct wclap_event_midi {
   wclap_event_header_t header;

   uint16_t port_index;
   uint8_t  data[3];
};
struct wclap_event_midi_sysex {
   wclap_event_header_t header;

   uint16_t       port_index;
   Pointer<const uint8_t> buffer;
   uint32_t       size;
};
struct wclap_event_midi2 {
   wclap_event_header_t header;

   uint16_t port_index;
   uint32_t data[4];
};
struct wclap_input_events {
   Pointer<void> ctx;
   Function<uint32_t,Pointer<const struct wclap_input_events> list> size;
   Function<Pointer<const wclap_event_header_t> ,Pointer<const struct wclap_input_events> list, uint32_t index> get;
};
struct wclap_output_events {
   Pointer<void> ctx;
   Function<bool,Pointer<const struct wclap_output_events> list,
                            Pointer<const wclap_event_header_t>       event> try_push;
};
struct wclap_audio_buffer {
   Pointer<Pointer<float>>  data32;
   Pointer<Pointer<double>> data64;
   uint32_t channel_count;
   uint32_t latency;
   uint64_t constant_mask;
};
typedef int32_t wclap_process_status;
struct wclap_process {
   int64_t steady_time;
   uint32_t frames_count;
   Pointer<const wclap_event_transport_t> transport;
   Pointer<const wclap_audio_buffer_t> audio_inputs;
   Pointer<wclap_audio_buffer_t>       audio_outputs;
   uint32_t                   audio_inputs_count;
   uint32_t                   audio_outputs_count;
   Pointer<const wclap_input_events_t>  in_events;
   Pointer<const wclap_output_events_t> out_events;
};
struct wclap_plugin_descriptor {
   wclap_version_t wclap_version;
   Pointer<const char> id;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> manual_url;
   Pointer<const char> support_url;
   Pointer<const char> version;
   Pointer<const char> description;
   Pointer<const char> Pointer<const> features;
};
struct wclap_plugin {
   Pointer<const wclap_plugin_descriptor_t> desc;

   Pointer<void> plugin_data;
   Function<bool,Pointer<const struct wclap_plugin> plugin> init;
   Function<void,Pointer<const struct wclap_plugin> plugin> destroy;
   Function<bool,Pointer<const struct wclap_plugin> plugin,
                            double                    sample_rate,
                            uint32_t                  min_frames_count,
                            uint32_t                  max_frames_count> activate;
   Function<void,Pointer<const struct wclap_plugin> plugin> deactivate;
   Function<bool,Pointer<const struct wclap_plugin> plugin> start_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> stop_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> reset;
   Function<wclap_process_status,Pointer<const struct wclap_plugin> plugin,
                                          Pointer<const wclap_process_t>     process> process;
   Function<Pointer<const void> ,Pointer<const struct wclap_plugin> plugin, Pointer<const char> id> get_extension;
   Function<void,Pointer<const struct wclap_plugin> plugin> on_main_thread;
};
struct wclap_istream {
   Pointer<void> ctx;
   Function<int64_t,Pointer<const struct wclap_istream> stream, Pointer<void> buffer, uint64_t size> read;
};
struct wclap_ostream {
   Pointer<void> ctx;
   Function<int64_t,Pointer<const struct wclap_ostream> stream, Pointer<const void> buffer, uint64_t size> write;
};
struct wclap_plugin_state {
   Function<bool,Pointer<const wclap_plugin_t> plugin, Pointer<const wclap_ostream_t> stream> save;
   Function<bool,Pointer<const wclap_plugin_t> plugin, Pointer<const wclap_istream_t> stream> load;
};
struct wclap_host_state {
   Function<void,Pointer<const wclap_host_t> host> mark_dirty;
};
struct wclap_version {
   uint32_t major;
   uint32_t minor;
   uint32_t revision;
};
struct wclap_host {
   wclap_version_t wclap_version;

   Pointer<void> host_data;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> version;
   Function<Pointer<const void> ,Pointer<const struct wclap_host> host, Pointer<const char> extension_id> get_extension;
   Function<void,Pointer<const struct wclap_host> host> request_restart;
   Function<void,Pointer<const struct wclap_host> host> request_process;
   Function<void,Pointer<const struct wclap_host> host> request_callback;
};
typedef int64_t wclap_beattime;
typedef int64_t wclap_sectime;
typedef uint32_t wclap_id;
typedef int32_t wclap_note_expression;
struct wclap_event_header {
   uint32_t size;
   uint32_t time;
   uint16_t space_id;
   uint16_t type;
   uint32_t flags;
};
struct wclap_event_note {
   wclap_event_header_t header;

   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;
   double  velocity;
};
struct wclap_event_note_expression {
   wclap_event_header_t header;

   wclap_note_expression expression_id;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_value {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_mod {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double amount;
};
struct wclap_event_param_gesture {
   wclap_event_header_t header;
   wclap_id param_id;
};
struct wclap_event_transport {
   wclap_event_header_t header;

   uint32_t flags;

   wclap_beattime song_pos_beats;
   wclap_sectime  song_pos_seconds;

   double tempo;
   double tempo_inc;

   wclap_beattime loop_start_beats;
   wclap_beattime loop_end_beats;
   wclap_sectime  loop_start_seconds;
   wclap_sectime  loop_end_seconds;

   wclap_beattime bar_start;
   int32_t       bar_number;

   uint16_t tsig_num;
   uint16_t tsig_denom;
};
struct wclap_event_midi {
   wclap_event_header_t header;

   uint16_t port_index;
   uint8_t  data[3];
};
struct wclap_event_midi_sysex {
   wclap_event_header_t header;

   uint16_t       port_index;
   Pointer<const uint8_t> buffer;
   uint32_t       size;
};
struct wclap_event_midi2 {
   wclap_event_header_t header;

   uint16_t port_index;
   uint32_t data[4];
};
struct wclap_input_events {
   Pointer<void> ctx;
   Function<uint32_t,Pointer<const struct wclap_input_events> list> size;
   Function<Pointer<const wclap_event_header_t> ,Pointer<const struct wclap_input_events> list, uint32_t index> get;
};
struct wclap_output_events {
   Pointer<void> ctx;
   Function<bool,Pointer<const struct wclap_output_events> list,
                            Pointer<const wclap_event_header_t>       event> try_push;
};
struct wclap_audio_buffer {
   Pointer<Pointer<float>>  data32;
   Pointer<Pointer<double>> data64;
   uint32_t channel_count;
   uint32_t latency;
   uint64_t constant_mask;
};
typedef int32_t wclap_process_status;
struct wclap_process {
   int64_t steady_time;
   uint32_t frames_count;
   Pointer<const wclap_event_transport_t> transport;
   Pointer<const wclap_audio_buffer_t> audio_inputs;
   Pointer<wclap_audio_buffer_t>       audio_outputs;
   uint32_t                   audio_inputs_count;
   uint32_t                   audio_outputs_count;
   Pointer<const wclap_input_events_t>  in_events;
   Pointer<const wclap_output_events_t> out_events;
};
struct wclap_plugin_descriptor {
   wclap_version_t wclap_version;
   Pointer<const char> id;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> manual_url;
   Pointer<const char> support_url;
   Pointer<const char> version;
   Pointer<const char> description;
   Pointer<const char> Pointer<const> features;
};
struct wclap_plugin {
   Pointer<const wclap_plugin_descriptor_t> desc;

   Pointer<void> plugin_data;
   Function<bool,Pointer<const struct wclap_plugin> plugin> init;
   Function<void,Pointer<const struct wclap_plugin> plugin> destroy;
   Function<bool,Pointer<const struct wclap_plugin> plugin,
                            double                    sample_rate,
                            uint32_t                  min_frames_count,
                            uint32_t                  max_frames_count> activate;
   Function<void,Pointer<const struct wclap_plugin> plugin> deactivate;
   Function<bool,Pointer<const struct wclap_plugin> plugin> start_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> stop_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> reset;
   Function<wclap_process_status,Pointer<const struct wclap_plugin> plugin,
                                          Pointer<const wclap_process_t>     process> process;
   Function<Pointer<const void> ,Pointer<const struct wclap_plugin> plugin, Pointer<const char> id> get_extension;
   Function<void,Pointer<const struct wclap_plugin> plugin> on_main_thread;
};
struct wclap_plugin_surround {
   Function<bool,Pointer<const wclap_plugin_t> plugin, uint64_t channel_mask> is_channel_mask_supported;
   Function<uint32_t,Pointer<const wclap_plugin_t> plugin,
                                       bool                 is_input,
                                       uint32_t             port_index,
                                       Pointer<uint8_t>             channel_map,
                                       uint32_t             channel_map_capacity> get_channel_map;
};
struct wclap_host_surround {
   Function<void,Pointer<const wclap_host_t> host> changed;
};
struct wclap_version {
   uint32_t major;
   uint32_t minor;
   uint32_t revision;
};
struct wclap_host {
   wclap_version_t wclap_version;

   Pointer<void> host_data;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> version;
   Function<Pointer<const void> ,Pointer<const struct wclap_host> host, Pointer<const char> extension_id> get_extension;
   Function<void,Pointer<const struct wclap_host> host> request_restart;
   Function<void,Pointer<const struct wclap_host> host> request_process;
   Function<void,Pointer<const struct wclap_host> host> request_callback;
};
typedef int64_t wclap_beattime;
typedef int64_t wclap_sectime;
typedef uint32_t wclap_id;
typedef int32_t wclap_note_expression;
struct wclap_event_header {
   uint32_t size;
   uint32_t time;
   uint16_t space_id;
   uint16_t type;
   uint32_t flags;
};
struct wclap_event_note {
   wclap_event_header_t header;

   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;
   double  velocity;
};
struct wclap_event_note_expression {
   wclap_event_header_t header;

   wclap_note_expression expression_id;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_value {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_mod {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double amount;
};
struct wclap_event_param_gesture {
   wclap_event_header_t header;
   wclap_id param_id;
};
struct wclap_event_transport {
   wclap_event_header_t header;

   uint32_t flags;

   wclap_beattime song_pos_beats;
   wclap_sectime  song_pos_seconds;

   double tempo;
   double tempo_inc;

   wclap_beattime loop_start_beats;
   wclap_beattime loop_end_beats;
   wclap_sectime  loop_start_seconds;
   wclap_sectime  loop_end_seconds;

   wclap_beattime bar_start;
   int32_t       bar_number;

   uint16_t tsig_num;
   uint16_t tsig_denom;
};
struct wclap_event_midi {
   wclap_event_header_t header;

   uint16_t port_index;
   uint8_t  data[3];
};
struct wclap_event_midi_sysex {
   wclap_event_header_t header;

   uint16_t       port_index;
   Pointer<const uint8_t> buffer;
   uint32_t       size;
};
struct wclap_event_midi2 {
   wclap_event_header_t header;

   uint16_t port_index;
   uint32_t data[4];
};
struct wclap_input_events {
   Pointer<void> ctx;
   Function<uint32_t,Pointer<const struct wclap_input_events> list> size;
   Function<Pointer<const wclap_event_header_t> ,Pointer<const struct wclap_input_events> list, uint32_t index> get;
};
struct wclap_output_events {
   Pointer<void> ctx;
   Function<bool,Pointer<const struct wclap_output_events> list,
                            Pointer<const wclap_event_header_t>       event> try_push;
};
struct wclap_audio_buffer {
   Pointer<Pointer<float>>  data32;
   Pointer<Pointer<double>> data64;
   uint32_t channel_count;
   uint32_t latency;
   uint64_t constant_mask;
};
typedef int32_t wclap_process_status;
struct wclap_process {
   int64_t steady_time;
   uint32_t frames_count;
   Pointer<const wclap_event_transport_t> transport;
   Pointer<const wclap_audio_buffer_t> audio_inputs;
   Pointer<wclap_audio_buffer_t>       audio_outputs;
   uint32_t                   audio_inputs_count;
   uint32_t                   audio_outputs_count;
   Pointer<const wclap_input_events_t>  in_events;
   Pointer<const wclap_output_events_t> out_events;
};
struct wclap_plugin_descriptor {
   wclap_version_t wclap_version;
   Pointer<const char> id;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> manual_url;
   Pointer<const char> support_url;
   Pointer<const char> version;
   Pointer<const char> description;
   Pointer<const char> Pointer<const> features;
};
struct wclap_plugin {
   Pointer<const wclap_plugin_descriptor_t> desc;

   Pointer<void> plugin_data;
   Function<bool,Pointer<const struct wclap_plugin> plugin> init;
   Function<void,Pointer<const struct wclap_plugin> plugin> destroy;
   Function<bool,Pointer<const struct wclap_plugin> plugin,
                            double                    sample_rate,
                            uint32_t                  min_frames_count,
                            uint32_t                  max_frames_count> activate;
   Function<void,Pointer<const struct wclap_plugin> plugin> deactivate;
   Function<bool,Pointer<const struct wclap_plugin> plugin> start_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> stop_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> reset;
   Function<wclap_process_status,Pointer<const struct wclap_plugin> plugin,
                                          Pointer<const wclap_process_t>     process> process;
   Function<Pointer<const void> ,Pointer<const struct wclap_plugin> plugin, Pointer<const char> id> get_extension;
   Function<void,Pointer<const struct wclap_plugin> plugin> on_main_thread;
};
struct wclap_plugin_tail {
   Function<uint32_t,Pointer<const wclap_plugin_t> plugin> get;
};
struct wclap_host_tail {
   Function<void,Pointer<const wclap_host_t> host> changed;
};
struct wclap_version {
   uint32_t major;
   uint32_t minor;
   uint32_t revision;
};
struct wclap_host {
   wclap_version_t wclap_version;

   Pointer<void> host_data;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> version;
   Function<Pointer<const void> ,Pointer<const struct wclap_host> host, Pointer<const char> extension_id> get_extension;
   Function<void,Pointer<const struct wclap_host> host> request_restart;
   Function<void,Pointer<const struct wclap_host> host> request_process;
   Function<void,Pointer<const struct wclap_host> host> request_callback;
};
typedef int64_t wclap_beattime;
typedef int64_t wclap_sectime;
typedef uint32_t wclap_id;
typedef int32_t wclap_note_expression;
struct wclap_event_header {
   uint32_t size;
   uint32_t time;
   uint16_t space_id;
   uint16_t type;
   uint32_t flags;
};
struct wclap_event_note {
   wclap_event_header_t header;

   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;
   double  velocity;
};
struct wclap_event_note_expression {
   wclap_event_header_t header;

   wclap_note_expression expression_id;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_value {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_mod {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double amount;
};
struct wclap_event_param_gesture {
   wclap_event_header_t header;
   wclap_id param_id;
};
struct wclap_event_transport {
   wclap_event_header_t header;

   uint32_t flags;

   wclap_beattime song_pos_beats;
   wclap_sectime  song_pos_seconds;

   double tempo;
   double tempo_inc;

   wclap_beattime loop_start_beats;
   wclap_beattime loop_end_beats;
   wclap_sectime  loop_start_seconds;
   wclap_sectime  loop_end_seconds;

   wclap_beattime bar_start;
   int32_t       bar_number;

   uint16_t tsig_num;
   uint16_t tsig_denom;
};
struct wclap_event_midi {
   wclap_event_header_t header;

   uint16_t port_index;
   uint8_t  data[3];
};
struct wclap_event_midi_sysex {
   wclap_event_header_t header;

   uint16_t       port_index;
   Pointer<const uint8_t> buffer;
   uint32_t       size;
};
struct wclap_event_midi2 {
   wclap_event_header_t header;

   uint16_t port_index;
   uint32_t data[4];
};
struct wclap_input_events {
   Pointer<void> ctx;
   Function<uint32_t,Pointer<const struct wclap_input_events> list> size;
   Function<Pointer<const wclap_event_header_t> ,Pointer<const struct wclap_input_events> list, uint32_t index> get;
};
struct wclap_output_events {
   Pointer<void> ctx;
   Function<bool,Pointer<const struct wclap_output_events> list,
                            Pointer<const wclap_event_header_t>       event> try_push;
};
struct wclap_audio_buffer {
   Pointer<Pointer<float>>  data32;
   Pointer<Pointer<double>> data64;
   uint32_t channel_count;
   uint32_t latency;
   uint64_t constant_mask;
};
typedef int32_t wclap_process_status;
struct wclap_process {
   int64_t steady_time;
   uint32_t frames_count;
   Pointer<const wclap_event_transport_t> transport;
   Pointer<const wclap_audio_buffer_t> audio_inputs;
   Pointer<wclap_audio_buffer_t>       audio_outputs;
   uint32_t                   audio_inputs_count;
   uint32_t                   audio_outputs_count;
   Pointer<const wclap_input_events_t>  in_events;
   Pointer<const wclap_output_events_t> out_events;
};
struct wclap_plugin_descriptor {
   wclap_version_t wclap_version;
   Pointer<const char> id;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> manual_url;
   Pointer<const char> support_url;
   Pointer<const char> version;
   Pointer<const char> description;
   Pointer<const char> Pointer<const> features;
};
struct wclap_plugin {
   Pointer<const wclap_plugin_descriptor_t> desc;

   Pointer<void> plugin_data;
   Function<bool,Pointer<const struct wclap_plugin> plugin> init;
   Function<void,Pointer<const struct wclap_plugin> plugin> destroy;
   Function<bool,Pointer<const struct wclap_plugin> plugin,
                            double                    sample_rate,
                            uint32_t                  min_frames_count,
                            uint32_t                  max_frames_count> activate;
   Function<void,Pointer<const struct wclap_plugin> plugin> deactivate;
   Function<bool,Pointer<const struct wclap_plugin> plugin> start_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> stop_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> reset;
   Function<wclap_process_status,Pointer<const struct wclap_plugin> plugin,
                                          Pointer<const wclap_process_t>     process> process;
   Function<Pointer<const void> ,Pointer<const struct wclap_plugin> plugin, Pointer<const char> id> get_extension;
   Function<void,Pointer<const struct wclap_plugin> plugin> on_main_thread;
};
struct wclap_host_thread_check {
   Function<bool,Pointer<const wclap_host_t> host> is_main_thread;
   Function<bool,Pointer<const wclap_host_t> host> is_audio_thread;
};
struct wclap_version {
   uint32_t major;
   uint32_t minor;
   uint32_t revision;
};
struct wclap_host {
   wclap_version_t wclap_version;

   Pointer<void> host_data;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> version;
   Function<Pointer<const void> ,Pointer<const struct wclap_host> host, Pointer<const char> extension_id> get_extension;
   Function<void,Pointer<const struct wclap_host> host> request_restart;
   Function<void,Pointer<const struct wclap_host> host> request_process;
   Function<void,Pointer<const struct wclap_host> host> request_callback;
};
typedef int64_t wclap_beattime;
typedef int64_t wclap_sectime;
typedef uint32_t wclap_id;
typedef int32_t wclap_note_expression;
struct wclap_event_header {
   uint32_t size;
   uint32_t time;
   uint16_t space_id;
   uint16_t type;
   uint32_t flags;
};
struct wclap_event_note {
   wclap_event_header_t header;

   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;
   double  velocity;
};
struct wclap_event_note_expression {
   wclap_event_header_t header;

   wclap_note_expression expression_id;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_value {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_mod {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double amount;
};
struct wclap_event_param_gesture {
   wclap_event_header_t header;
   wclap_id param_id;
};
struct wclap_event_transport {
   wclap_event_header_t header;

   uint32_t flags;

   wclap_beattime song_pos_beats;
   wclap_sectime  song_pos_seconds;

   double tempo;
   double tempo_inc;

   wclap_beattime loop_start_beats;
   wclap_beattime loop_end_beats;
   wclap_sectime  loop_start_seconds;
   wclap_sectime  loop_end_seconds;

   wclap_beattime bar_start;
   int32_t       bar_number;

   uint16_t tsig_num;
   uint16_t tsig_denom;
};
struct wclap_event_midi {
   wclap_event_header_t header;

   uint16_t port_index;
   uint8_t  data[3];
};
struct wclap_event_midi_sysex {
   wclap_event_header_t header;

   uint16_t       port_index;
   Pointer<const uint8_t> buffer;
   uint32_t       size;
};
struct wclap_event_midi2 {
   wclap_event_header_t header;

   uint16_t port_index;
   uint32_t data[4];
};
struct wclap_input_events {
   Pointer<void> ctx;
   Function<uint32_t,Pointer<const struct wclap_input_events> list> size;
   Function<Pointer<const wclap_event_header_t> ,Pointer<const struct wclap_input_events> list, uint32_t index> get;
};
struct wclap_output_events {
   Pointer<void> ctx;
   Function<bool,Pointer<const struct wclap_output_events> list,
                            Pointer<const wclap_event_header_t>       event> try_push;
};
struct wclap_audio_buffer {
   Pointer<Pointer<float>>  data32;
   Pointer<Pointer<double>> data64;
   uint32_t channel_count;
   uint32_t latency;
   uint64_t constant_mask;
};
typedef int32_t wclap_process_status;
struct wclap_process {
   int64_t steady_time;
   uint32_t frames_count;
   Pointer<const wclap_event_transport_t> transport;
   Pointer<const wclap_audio_buffer_t> audio_inputs;
   Pointer<wclap_audio_buffer_t>       audio_outputs;
   uint32_t                   audio_inputs_count;
   uint32_t                   audio_outputs_count;
   Pointer<const wclap_input_events_t>  in_events;
   Pointer<const wclap_output_events_t> out_events;
};
struct wclap_plugin_descriptor {
   wclap_version_t wclap_version;
   Pointer<const char> id;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> manual_url;
   Pointer<const char> support_url;
   Pointer<const char> version;
   Pointer<const char> description;
   Pointer<const char> Pointer<const> features;
};
struct wclap_plugin {
   Pointer<const wclap_plugin_descriptor_t> desc;

   Pointer<void> plugin_data;
   Function<bool,Pointer<const struct wclap_plugin> plugin> init;
   Function<void,Pointer<const struct wclap_plugin> plugin> destroy;
   Function<bool,Pointer<const struct wclap_plugin> plugin,
                            double                    sample_rate,
                            uint32_t                  min_frames_count,
                            uint32_t                  max_frames_count> activate;
   Function<void,Pointer<const struct wclap_plugin> plugin> deactivate;
   Function<bool,Pointer<const struct wclap_plugin> plugin> start_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> stop_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> reset;
   Function<wclap_process_status,Pointer<const struct wclap_plugin> plugin,
                                          Pointer<const wclap_process_t>     process> process;
   Function<Pointer<const void> ,Pointer<const struct wclap_plugin> plugin, Pointer<const char> id> get_extension;
   Function<void,Pointer<const struct wclap_plugin> plugin> on_main_thread;
};
struct wclap_plugin_thread_pool {
   Function<void,Pointer<const wclap_plugin_t> plugin, uint32_t task_index> exec;
};
struct wclap_host_thread_pool {
   Function<bool,Pointer<const wclap_host_t> host, uint32_t num_tasks> request_exec;
};
struct wclap_version {
   uint32_t major;
   uint32_t minor;
   uint32_t revision;
};
struct wclap_host {
   wclap_version_t wclap_version;

   Pointer<void> host_data;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> version;
   Function<Pointer<const void> ,Pointer<const struct wclap_host> host, Pointer<const char> extension_id> get_extension;
   Function<void,Pointer<const struct wclap_host> host> request_restart;
   Function<void,Pointer<const struct wclap_host> host> request_process;
   Function<void,Pointer<const struct wclap_host> host> request_callback;
};
typedef int64_t wclap_beattime;
typedef int64_t wclap_sectime;
typedef uint32_t wclap_id;
typedef int32_t wclap_note_expression;
struct wclap_event_header {
   uint32_t size;
   uint32_t time;
   uint16_t space_id;
   uint16_t type;
   uint32_t flags;
};
struct wclap_event_note {
   wclap_event_header_t header;

   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;
   double  velocity;
};
struct wclap_event_note_expression {
   wclap_event_header_t header;

   wclap_note_expression expression_id;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_value {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_mod {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double amount;
};
struct wclap_event_param_gesture {
   wclap_event_header_t header;
   wclap_id param_id;
};
struct wclap_event_transport {
   wclap_event_header_t header;

   uint32_t flags;

   wclap_beattime song_pos_beats;
   wclap_sectime  song_pos_seconds;

   double tempo;
   double tempo_inc;

   wclap_beattime loop_start_beats;
   wclap_beattime loop_end_beats;
   wclap_sectime  loop_start_seconds;
   wclap_sectime  loop_end_seconds;

   wclap_beattime bar_start;
   int32_t       bar_number;

   uint16_t tsig_num;
   uint16_t tsig_denom;
};
struct wclap_event_midi {
   wclap_event_header_t header;

   uint16_t port_index;
   uint8_t  data[3];
};
struct wclap_event_midi_sysex {
   wclap_event_header_t header;

   uint16_t       port_index;
   Pointer<const uint8_t> buffer;
   uint32_t       size;
};
struct wclap_event_midi2 {
   wclap_event_header_t header;

   uint16_t port_index;
   uint32_t data[4];
};
struct wclap_input_events {
   Pointer<void> ctx;
   Function<uint32_t,Pointer<const struct wclap_input_events> list> size;
   Function<Pointer<const wclap_event_header_t> ,Pointer<const struct wclap_input_events> list, uint32_t index> get;
};
struct wclap_output_events {
   Pointer<void> ctx;
   Function<bool,Pointer<const struct wclap_output_events> list,
                            Pointer<const wclap_event_header_t>       event> try_push;
};
struct wclap_audio_buffer {
   Pointer<Pointer<float>>  data32;
   Pointer<Pointer<double>> data64;
   uint32_t channel_count;
   uint32_t latency;
   uint64_t constant_mask;
};
typedef int32_t wclap_process_status;
struct wclap_process {
   int64_t steady_time;
   uint32_t frames_count;
   Pointer<const wclap_event_transport_t> transport;
   Pointer<const wclap_audio_buffer_t> audio_inputs;
   Pointer<wclap_audio_buffer_t>       audio_outputs;
   uint32_t                   audio_inputs_count;
   uint32_t                   audio_outputs_count;
   Pointer<const wclap_input_events_t>  in_events;
   Pointer<const wclap_output_events_t> out_events;
};
struct wclap_plugin_descriptor {
   wclap_version_t wclap_version;
   Pointer<const char> id;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> manual_url;
   Pointer<const char> support_url;
   Pointer<const char> version;
   Pointer<const char> description;
   Pointer<const char> Pointer<const> features;
};
struct wclap_plugin {
   Pointer<const wclap_plugin_descriptor_t> desc;

   Pointer<void> plugin_data;
   Function<bool,Pointer<const struct wclap_plugin> plugin> init;
   Function<void,Pointer<const struct wclap_plugin> plugin> destroy;
   Function<bool,Pointer<const struct wclap_plugin> plugin,
                            double                    sample_rate,
                            uint32_t                  min_frames_count,
                            uint32_t                  max_frames_count> activate;
   Function<void,Pointer<const struct wclap_plugin> plugin> deactivate;
   Function<bool,Pointer<const struct wclap_plugin> plugin> start_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> stop_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> reset;
   Function<wclap_process_status,Pointer<const struct wclap_plugin> plugin,
                                          Pointer<const wclap_process_t>     process> process;
   Function<Pointer<const void> ,Pointer<const struct wclap_plugin> plugin, Pointer<const char> id> get_extension;
   Function<void,Pointer<const struct wclap_plugin> plugin> on_main_thread;
};
struct wclap_plugin_timer_support {
   Function<void,Pointer<const wclap_plugin_t> plugin, wclap_id timer_id> on_timer;
};
struct wclap_host_timer_support {
   Function<bool,Pointer<const wclap_host_t> host, uint32_t period_ms, Pointer<wclap_id> timer_id> register_timer;
   Function<bool,Pointer<const wclap_host_t> host, wclap_id timer_id> unregister_timer;
};
struct wclap_version {
   uint32_t major;
   uint32_t minor;
   uint32_t revision;
};
struct wclap_host {
   wclap_version_t wclap_version;

   Pointer<void> host_data;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> version;
   Function<Pointer<const void> ,Pointer<const struct wclap_host> host, Pointer<const char> extension_id> get_extension;
   Function<void,Pointer<const struct wclap_host> host> request_restart;
   Function<void,Pointer<const struct wclap_host> host> request_process;
   Function<void,Pointer<const struct wclap_host> host> request_callback;
};
typedef int64_t wclap_beattime;
typedef int64_t wclap_sectime;
typedef uint32_t wclap_id;
typedef int32_t wclap_note_expression;
struct wclap_event_header {
   uint32_t size;
   uint32_t time;
   uint16_t space_id;
   uint16_t type;
   uint32_t flags;
};
struct wclap_event_note {
   wclap_event_header_t header;

   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;
   double  velocity;
};
struct wclap_event_note_expression {
   wclap_event_header_t header;

   wclap_note_expression expression_id;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_value {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_mod {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double amount;
};
struct wclap_event_param_gesture {
   wclap_event_header_t header;
   wclap_id param_id;
};
struct wclap_event_transport {
   wclap_event_header_t header;

   uint32_t flags;

   wclap_beattime song_pos_beats;
   wclap_sectime  song_pos_seconds;

   double tempo;
   double tempo_inc;

   wclap_beattime loop_start_beats;
   wclap_beattime loop_end_beats;
   wclap_sectime  loop_start_seconds;
   wclap_sectime  loop_end_seconds;

   wclap_beattime bar_start;
   int32_t       bar_number;

   uint16_t tsig_num;
   uint16_t tsig_denom;
};
struct wclap_event_midi {
   wclap_event_header_t header;

   uint16_t port_index;
   uint8_t  data[3];
};
struct wclap_event_midi_sysex {
   wclap_event_header_t header;

   uint16_t       port_index;
   Pointer<const uint8_t> buffer;
   uint32_t       size;
};
struct wclap_event_midi2 {
   wclap_event_header_t header;

   uint16_t port_index;
   uint32_t data[4];
};
struct wclap_input_events {
   Pointer<void> ctx;
   Function<uint32_t,Pointer<const struct wclap_input_events> list> size;
   Function<Pointer<const wclap_event_header_t> ,Pointer<const struct wclap_input_events> list, uint32_t index> get;
};
struct wclap_output_events {
   Pointer<void> ctx;
   Function<bool,Pointer<const struct wclap_output_events> list,
                            Pointer<const wclap_event_header_t>       event> try_push;
};
struct wclap_audio_buffer {
   Pointer<Pointer<float>>  data32;
   Pointer<Pointer<double>> data64;
   uint32_t channel_count;
   uint32_t latency;
   uint64_t constant_mask;
};
typedef int32_t wclap_process_status;
struct wclap_process {
   int64_t steady_time;
   uint32_t frames_count;
   Pointer<const wclap_event_transport_t> transport;
   Pointer<const wclap_audio_buffer_t> audio_inputs;
   Pointer<wclap_audio_buffer_t>       audio_outputs;
   uint32_t                   audio_inputs_count;
   uint32_t                   audio_outputs_count;
   Pointer<const wclap_input_events_t>  in_events;
   Pointer<const wclap_output_events_t> out_events;
};
struct wclap_plugin_descriptor {
   wclap_version_t wclap_version;
   Pointer<const char> id;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> manual_url;
   Pointer<const char> support_url;
   Pointer<const char> version;
   Pointer<const char> description;
   Pointer<const char> Pointer<const> features;
};
struct wclap_plugin {
   Pointer<const wclap_plugin_descriptor_t> desc;

   Pointer<void> plugin_data;
   Function<bool,Pointer<const struct wclap_plugin> plugin> init;
   Function<void,Pointer<const struct wclap_plugin> plugin> destroy;
   Function<bool,Pointer<const struct wclap_plugin> plugin,
                            double                    sample_rate,
                            uint32_t                  min_frames_count,
                            uint32_t                  max_frames_count> activate;
   Function<void,Pointer<const struct wclap_plugin> plugin> deactivate;
   Function<bool,Pointer<const struct wclap_plugin> plugin> start_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> stop_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> reset;
   Function<wclap_process_status,Pointer<const struct wclap_plugin> plugin,
                                          Pointer<const wclap_process_t>     process> process;
   Function<Pointer<const void> ,Pointer<const struct wclap_plugin> plugin, Pointer<const char> id> get_extension;
   Function<void,Pointer<const struct wclap_plugin> plugin> on_main_thread;
};
struct wclap_color {
   uint8_t alpha;
   uint8_t red;
   uint8_t green;
   uint8_t blue;
};
struct wclap_track_info {
   uint64_t flags;
   char name[CLAP_NAME_SIZE];
   wclap_color_t color;
   int32_t     audio_channel_count;
   Pointer<const char> audio_port_type;
};
struct wclap_plugin_track_info {
   Function<void,Pointer<const wclap_plugin_t> plugin> changed;
};
struct wclap_host_track_info {
   Function<bool,Pointer<const wclap_host_t> host, Pointer<wclap_track_info_t> info> get;
};
struct wclap_version {
   uint32_t major;
   uint32_t minor;
   uint32_t revision;
};
struct wclap_host {
   wclap_version_t wclap_version;

   Pointer<void> host_data;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> version;
   Function<Pointer<const void> ,Pointer<const struct wclap_host> host, Pointer<const char> extension_id> get_extension;
   Function<void,Pointer<const struct wclap_host> host> request_restart;
   Function<void,Pointer<const struct wclap_host> host> request_process;
   Function<void,Pointer<const struct wclap_host> host> request_callback;
};
typedef int64_t wclap_beattime;
typedef int64_t wclap_sectime;
typedef uint32_t wclap_id;
typedef int32_t wclap_note_expression;
struct wclap_event_header {
   uint32_t size;
   uint32_t time;
   uint16_t space_id;
   uint16_t type;
   uint32_t flags;
};
struct wclap_event_note {
   wclap_event_header_t header;

   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;
   double  velocity;
};
struct wclap_event_note_expression {
   wclap_event_header_t header;

   wclap_note_expression expression_id;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_value {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_mod {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double amount;
};
struct wclap_event_param_gesture {
   wclap_event_header_t header;
   wclap_id param_id;
};
struct wclap_event_transport {
   wclap_event_header_t header;

   uint32_t flags;

   wclap_beattime song_pos_beats;
   wclap_sectime  song_pos_seconds;

   double tempo;
   double tempo_inc;

   wclap_beattime loop_start_beats;
   wclap_beattime loop_end_beats;
   wclap_sectime  loop_start_seconds;
   wclap_sectime  loop_end_seconds;

   wclap_beattime bar_start;
   int32_t       bar_number;

   uint16_t tsig_num;
   uint16_t tsig_denom;
};
struct wclap_event_midi {
   wclap_event_header_t header;

   uint16_t port_index;
   uint8_t  data[3];
};
struct wclap_event_midi_sysex {
   wclap_event_header_t header;

   uint16_t       port_index;
   Pointer<const uint8_t> buffer;
   uint32_t       size;
};
struct wclap_event_midi2 {
   wclap_event_header_t header;

   uint16_t port_index;
   uint32_t data[4];
};
struct wclap_input_events {
   Pointer<void> ctx;
   Function<uint32_t,Pointer<const struct wclap_input_events> list> size;
   Function<Pointer<const wclap_event_header_t> ,Pointer<const struct wclap_input_events> list, uint32_t index> get;
};
struct wclap_output_events {
   Pointer<void> ctx;
   Function<bool,Pointer<const struct wclap_output_events> list,
                            Pointer<const wclap_event_header_t>       event> try_push;
};
struct wclap_audio_buffer {
   Pointer<Pointer<float>>  data32;
   Pointer<Pointer<double>> data64;
   uint32_t channel_count;
   uint32_t latency;
   uint64_t constant_mask;
};
typedef int32_t wclap_process_status;
struct wclap_process {
   int64_t steady_time;
   uint32_t frames_count;
   Pointer<const wclap_event_transport_t> transport;
   Pointer<const wclap_audio_buffer_t> audio_inputs;
   Pointer<wclap_audio_buffer_t>       audio_outputs;
   uint32_t                   audio_inputs_count;
   uint32_t                   audio_outputs_count;
   Pointer<const wclap_input_events_t>  in_events;
   Pointer<const wclap_output_events_t> out_events;
};
struct wclap_plugin_descriptor {
   wclap_version_t wclap_version;
   Pointer<const char> id;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> manual_url;
   Pointer<const char> support_url;
   Pointer<const char> version;
   Pointer<const char> description;
   Pointer<const char> Pointer<const> features;
};
struct wclap_plugin {
   Pointer<const wclap_plugin_descriptor_t> desc;

   Pointer<void> plugin_data;
   Function<bool,Pointer<const struct wclap_plugin> plugin> init;
   Function<void,Pointer<const struct wclap_plugin> plugin> destroy;
   Function<bool,Pointer<const struct wclap_plugin> plugin,
                            double                    sample_rate,
                            uint32_t                  min_frames_count,
                            uint32_t                  max_frames_count> activate;
   Function<void,Pointer<const struct wclap_plugin> plugin> deactivate;
   Function<bool,Pointer<const struct wclap_plugin> plugin> start_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> stop_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> reset;
   Function<wclap_process_status,Pointer<const struct wclap_plugin> plugin,
                                          Pointer<const wclap_process_t>     process> process;
   Function<Pointer<const void> ,Pointer<const struct wclap_plugin> plugin, Pointer<const char> id> get_extension;
   Function<void,Pointer<const struct wclap_plugin> plugin> on_main_thread;
};
struct wclap_voice_info {
   uint32_t voice_count;
   uint32_t voice_capacity;

   uint64_t flags;
};
struct wclap_plugin_voice_info {
   Function<bool,Pointer<const wclap_plugin_t> plugin, Pointer<wclap_voice_info_t> info> get;
};
struct wclap_host_voice_info {
   Function<void,Pointer<const wclap_host_t> host> changed;
};
struct wclap_plugin_invalidation_source {
   Pointer<const char> directory;
   Pointer<const char> filename_glob;
   bool recursive_scan;
};
struct wclap_plugin_invalidation_factory {
   Function<uint32_t,Pointer<const struct wclap_plugin_invalidation_factory> factory> count;
   Function<Pointer<const wclap_plugin_invalidation_source_t> ,
      Pointer<const struct wclap_plugin_invalidation_factory> factory, uint32_t index> get;
   Function<bool,Pointer<const struct wclap_plugin_invalidation_factory> factory> refresh;
};
typedef uint32_t wclap_id;
struct wclap_universal_plugin_id {
   Pointer<const char> abi;
   Pointer<const char> id;
};
struct wclap_istream {
   Pointer<void> ctx;
   Function<int64_t,Pointer<const struct wclap_istream> stream, Pointer<void> buffer, uint64_t size> read;
};
struct wclap_ostream {
   Pointer<void> ctx;
   Function<int64_t,Pointer<const struct wclap_ostream> stream, Pointer<const void> buffer, uint64_t size> write;
};
struct wclap_version {
   uint32_t major;
   uint32_t minor;
   uint32_t revision;
};
struct wclap_plugin_state_converter_descriptor {
   wclap_version_t wclap_version;

   wclap_universal_plugin_id_t src_plugin_id;
   wclap_universal_plugin_id_t dst_plugin_id;

   Pointer<const char> id;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> version;
   Pointer<const char> description;
};
struct wclap_plugin_state_converter {
   Pointer<const wclap_plugin_state_converter_descriptor_t> desc;

   Pointer<void> converter_data;
   Function<void ,Pointer<struct wclap_plugin_state_converter> converter> destroy;
   Function<bool ,Pointer<struct wclap_plugin_state_converter> converter,
                         Pointer<const wclap_istream_t>               src,
                         Pointer<const wclap_ostream_t>               dst,
                         Pointer<char>                               error_buffer,
                         size_t                              error_buffer_size> convert_state;
   Function<bool ,Pointer<struct wclap_plugin_state_converter> converter,
                                    wclap_id                             src_param_id,
                                    double                              src_normalized_value,
                                    Pointer<wclap_id>                            dst_param_id,
                                    Pointer<double>                             dst_normalized_value> convert_normalized_value;
   Function<bool ,Pointer<struct wclap_plugin_state_converter> converter,
                               wclap_id                             src_param_id,
                               double                              src_plain_value,
                               Pointer<wclap_id>                            dst_param_id,
                               Pointer<double>                             dst_plain_value> convert_plain_value;
};
struct wclap_plugin_state_converter_factory {
   Function<uint32_t ,Pointer<const struct wclap_plugin_state_converter_factory> factory> count;
   Function<Pointer<const wclap_plugin_state_converter_descriptor_t> ,
      Pointer<const struct wclap_plugin_state_converter_factory> factory, uint32_t index> get_descriptor;
   Function<Pointer<wclap_plugin_state_converter_t> ,
      Pointer<const struct wclap_plugin_state_converter_factory> factory, Pointer<const char> converter_id> create;
};
struct wclap_version {
   uint32_t major;
   uint32_t minor;
   uint32_t revision;
};
struct wclap_host {
   wclap_version_t wclap_version;

   Pointer<void> host_data;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> version;
   Function<Pointer<const void> ,Pointer<const struct wclap_host> host, Pointer<const char> extension_id> get_extension;
   Function<void,Pointer<const struct wclap_host> host> request_restart;
   Function<void,Pointer<const struct wclap_host> host> request_process;
   Function<void,Pointer<const struct wclap_host> host> request_callback;
};
typedef int64_t wclap_beattime;
typedef int64_t wclap_sectime;
typedef uint32_t wclap_id;
typedef int32_t wclap_note_expression;
struct wclap_event_header {
   uint32_t size;
   uint32_t time;
   uint16_t space_id;
   uint16_t type;
   uint32_t flags;
};
struct wclap_event_note {
   wclap_event_header_t header;

   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;
   double  velocity;
};
struct wclap_event_note_expression {
   wclap_event_header_t header;

   wclap_note_expression expression_id;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_value {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_mod {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double amount;
};
struct wclap_event_param_gesture {
   wclap_event_header_t header;
   wclap_id param_id;
};
struct wclap_event_transport {
   wclap_event_header_t header;

   uint32_t flags;

   wclap_beattime song_pos_beats;
   wclap_sectime  song_pos_seconds;

   double tempo;
   double tempo_inc;

   wclap_beattime loop_start_beats;
   wclap_beattime loop_end_beats;
   wclap_sectime  loop_start_seconds;
   wclap_sectime  loop_end_seconds;

   wclap_beattime bar_start;
   int32_t       bar_number;

   uint16_t tsig_num;
   uint16_t tsig_denom;
};
struct wclap_event_midi {
   wclap_event_header_t header;

   uint16_t port_index;
   uint8_t  data[3];
};
struct wclap_event_midi_sysex {
   wclap_event_header_t header;

   uint16_t       port_index;
   Pointer<const uint8_t> buffer;
   uint32_t       size;
};
struct wclap_event_midi2 {
   wclap_event_header_t header;

   uint16_t port_index;
   uint32_t data[4];
};
struct wclap_input_events {
   Pointer<void> ctx;
   Function<uint32_t,Pointer<const struct wclap_input_events> list> size;
   Function<Pointer<const wclap_event_header_t> ,Pointer<const struct wclap_input_events> list, uint32_t index> get;
};
struct wclap_output_events {
   Pointer<void> ctx;
   Function<bool,Pointer<const struct wclap_output_events> list,
                            Pointer<const wclap_event_header_t>       event> try_push;
};
struct wclap_audio_buffer {
   Pointer<Pointer<float>>  data32;
   Pointer<Pointer<double>> data64;
   uint32_t channel_count;
   uint32_t latency;
   uint64_t constant_mask;
};
typedef int32_t wclap_process_status;
struct wclap_process {
   int64_t steady_time;
   uint32_t frames_count;
   Pointer<const wclap_event_transport_t> transport;
   Pointer<const wclap_audio_buffer_t> audio_inputs;
   Pointer<wclap_audio_buffer_t>       audio_outputs;
   uint32_t                   audio_inputs_count;
   uint32_t                   audio_outputs_count;
   Pointer<const wclap_input_events_t>  in_events;
   Pointer<const wclap_output_events_t> out_events;
};
struct wclap_plugin_descriptor {
   wclap_version_t wclap_version;
   Pointer<const char> id;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> manual_url;
   Pointer<const char> support_url;
   Pointer<const char> version;
   Pointer<const char> description;
   Pointer<const char> Pointer<const> features;
};
struct wclap_plugin {
   Pointer<const wclap_plugin_descriptor_t> desc;

   Pointer<void> plugin_data;
   Function<bool,Pointer<const struct wclap_plugin> plugin> init;
   Function<void,Pointer<const struct wclap_plugin> plugin> destroy;
   Function<bool,Pointer<const struct wclap_plugin> plugin,
                            double                    sample_rate,
                            uint32_t                  min_frames_count,
                            uint32_t                  max_frames_count> activate;
   Function<void,Pointer<const struct wclap_plugin> plugin> deactivate;
   Function<bool,Pointer<const struct wclap_plugin> plugin> start_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> stop_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> reset;
   Function<wclap_process_status,Pointer<const struct wclap_plugin> plugin,
                                          Pointer<const wclap_process_t>     process> process;
   Function<Pointer<const void> ,Pointer<const struct wclap_plugin> plugin, Pointer<const char> id> get_extension;
   Function<void,Pointer<const struct wclap_plugin> plugin> on_main_thread;
};
struct wclap_audio_port_info {
   wclap_id id;
   char    name[CLAP_NAME_SIZE];

   uint32_t flags;
   uint32_t channel_count;
   Pointer<const char> port_type;
   wclap_id in_place_pair;
};
struct wclap_plugin_audio_ports {
   Function<uint32_t,Pointer<const wclap_plugin_t> plugin, bool is_input> count;
   Function<bool,Pointer<const wclap_plugin_t>    plugin,
                       uint32_t                index,
                       bool                    is_input,
                       Pointer<wclap_audio_port_info_t> info> get;
};
struct wclap_host_audio_ports {
   Function<bool,Pointer<const wclap_host_t> host, uint32_t flag> is_rescan_flag_supported;
   Function<void,Pointer<const wclap_host_t> host, uint32_t flags> rescan;
};
struct wclap_plugin_extensible_audio_ports {
   Function<bool,Pointer<const wclap_plugin_t> plugin,
                            bool                 is_input,
                            uint32_t             channel_count,
                            Pointer<const char>          port_type,
                            Pointer<const void>          port_details> add_port;
   Function<bool,Pointer<const wclap_plugin_t> plugin, bool is_input, uint32_t index> remove_port;
};
struct wclap_version {
   uint32_t major;
   uint32_t minor;
   uint32_t revision;
};
struct wclap_host {
   wclap_version_t wclap_version;

   Pointer<void> host_data;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> version;
   Function<Pointer<const void> ,Pointer<const struct wclap_host> host, Pointer<const char> extension_id> get_extension;
   Function<void,Pointer<const struct wclap_host> host> request_restart;
   Function<void,Pointer<const struct wclap_host> host> request_process;
   Function<void,Pointer<const struct wclap_host> host> request_callback;
};
typedef int64_t wclap_beattime;
typedef int64_t wclap_sectime;
typedef uint32_t wclap_id;
typedef int32_t wclap_note_expression;
struct wclap_event_header {
   uint32_t size;
   uint32_t time;
   uint16_t space_id;
   uint16_t type;
   uint32_t flags;
};
struct wclap_event_note {
   wclap_event_header_t header;

   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;
   double  velocity;
};
struct wclap_event_note_expression {
   wclap_event_header_t header;

   wclap_note_expression expression_id;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_value {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_mod {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double amount;
};
struct wclap_event_param_gesture {
   wclap_event_header_t header;
   wclap_id param_id;
};
struct wclap_event_transport {
   wclap_event_header_t header;

   uint32_t flags;

   wclap_beattime song_pos_beats;
   wclap_sectime  song_pos_seconds;

   double tempo;
   double tempo_inc;

   wclap_beattime loop_start_beats;
   wclap_beattime loop_end_beats;
   wclap_sectime  loop_start_seconds;
   wclap_sectime  loop_end_seconds;

   wclap_beattime bar_start;
   int32_t       bar_number;

   uint16_t tsig_num;
   uint16_t tsig_denom;
};
struct wclap_event_midi {
   wclap_event_header_t header;

   uint16_t port_index;
   uint8_t  data[3];
};
struct wclap_event_midi_sysex {
   wclap_event_header_t header;

   uint16_t       port_index;
   Pointer<const uint8_t> buffer;
   uint32_t       size;
};
struct wclap_event_midi2 {
   wclap_event_header_t header;

   uint16_t port_index;
   uint32_t data[4];
};
struct wclap_input_events {
   Pointer<void> ctx;
   Function<uint32_t,Pointer<const struct wclap_input_events> list> size;
   Function<Pointer<const wclap_event_header_t> ,Pointer<const struct wclap_input_events> list, uint32_t index> get;
};
struct wclap_output_events {
   Pointer<void> ctx;
   Function<bool,Pointer<const struct wclap_output_events> list,
                            Pointer<const wclap_event_header_t>       event> try_push;
};
struct wclap_audio_buffer {
   Pointer<Pointer<float>>  data32;
   Pointer<Pointer<double>> data64;
   uint32_t channel_count;
   uint32_t latency;
   uint64_t constant_mask;
};
typedef int32_t wclap_process_status;
struct wclap_process {
   int64_t steady_time;
   uint32_t frames_count;
   Pointer<const wclap_event_transport_t> transport;
   Pointer<const wclap_audio_buffer_t> audio_inputs;
   Pointer<wclap_audio_buffer_t>       audio_outputs;
   uint32_t                   audio_inputs_count;
   uint32_t                   audio_outputs_count;
   Pointer<const wclap_input_events_t>  in_events;
   Pointer<const wclap_output_events_t> out_events;
};
struct wclap_plugin_descriptor {
   wclap_version_t wclap_version;
   Pointer<const char> id;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> manual_url;
   Pointer<const char> support_url;
   Pointer<const char> version;
   Pointer<const char> description;
   Pointer<const char> Pointer<const> features;
};
struct wclap_plugin {
   Pointer<const wclap_plugin_descriptor_t> desc;

   Pointer<void> plugin_data;
   Function<bool,Pointer<const struct wclap_plugin> plugin> init;
   Function<void,Pointer<const struct wclap_plugin> plugin> destroy;
   Function<bool,Pointer<const struct wclap_plugin> plugin,
                            double                    sample_rate,
                            uint32_t                  min_frames_count,
                            uint32_t                  max_frames_count> activate;
   Function<void,Pointer<const struct wclap_plugin> plugin> deactivate;
   Function<bool,Pointer<const struct wclap_plugin> plugin> start_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> stop_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> reset;
   Function<wclap_process_status,Pointer<const struct wclap_plugin> plugin,
                                          Pointer<const wclap_process_t>     process> process;
   Function<Pointer<const void> ,Pointer<const struct wclap_plugin> plugin, Pointer<const char> id> get_extension;
   Function<void,Pointer<const struct wclap_plugin> plugin> on_main_thread;
};
struct wclap_plugin_gain_adjustment_metering {
  Function<double,Pointer<const wclap_plugin_t> plugin> get;
};
struct wclap_version {
   uint32_t major;
   uint32_t minor;
   uint32_t revision;
};
struct wclap_host {
   wclap_version_t wclap_version;

   Pointer<void> host_data;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> version;
   Function<Pointer<const void> ,Pointer<const struct wclap_host> host, Pointer<const char> extension_id> get_extension;
   Function<void,Pointer<const struct wclap_host> host> request_restart;
   Function<void,Pointer<const struct wclap_host> host> request_process;
   Function<void,Pointer<const struct wclap_host> host> request_callback;
};
typedef int64_t wclap_beattime;
typedef int64_t wclap_sectime;
typedef uint32_t wclap_id;
typedef int32_t wclap_note_expression;
struct wclap_event_header {
   uint32_t size;
   uint32_t time;
   uint16_t space_id;
   uint16_t type;
   uint32_t flags;
};
struct wclap_event_note {
   wclap_event_header_t header;

   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;
   double  velocity;
};
struct wclap_event_note_expression {
   wclap_event_header_t header;

   wclap_note_expression expression_id;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_value {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_mod {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double amount;
};
struct wclap_event_param_gesture {
   wclap_event_header_t header;
   wclap_id param_id;
};
struct wclap_event_transport {
   wclap_event_header_t header;

   uint32_t flags;

   wclap_beattime song_pos_beats;
   wclap_sectime  song_pos_seconds;

   double tempo;
   double tempo_inc;

   wclap_beattime loop_start_beats;
   wclap_beattime loop_end_beats;
   wclap_sectime  loop_start_seconds;
   wclap_sectime  loop_end_seconds;

   wclap_beattime bar_start;
   int32_t       bar_number;

   uint16_t tsig_num;
   uint16_t tsig_denom;
};
struct wclap_event_midi {
   wclap_event_header_t header;

   uint16_t port_index;
   uint8_t  data[3];
};
struct wclap_event_midi_sysex {
   wclap_event_header_t header;

   uint16_t       port_index;
   Pointer<const uint8_t> buffer;
   uint32_t       size;
};
struct wclap_event_midi2 {
   wclap_event_header_t header;

   uint16_t port_index;
   uint32_t data[4];
};
struct wclap_input_events {
   Pointer<void> ctx;
   Function<uint32_t,Pointer<const struct wclap_input_events> list> size;
   Function<Pointer<const wclap_event_header_t> ,Pointer<const struct wclap_input_events> list, uint32_t index> get;
};
struct wclap_output_events {
   Pointer<void> ctx;
   Function<bool,Pointer<const struct wclap_output_events> list,
                            Pointer<const wclap_event_header_t>       event> try_push;
};
struct wclap_audio_buffer {
   Pointer<Pointer<float>>  data32;
   Pointer<Pointer<double>> data64;
   uint32_t channel_count;
   uint32_t latency;
   uint64_t constant_mask;
};
typedef int32_t wclap_process_status;
struct wclap_process {
   int64_t steady_time;
   uint32_t frames_count;
   Pointer<const wclap_event_transport_t> transport;
   Pointer<const wclap_audio_buffer_t> audio_inputs;
   Pointer<wclap_audio_buffer_t>       audio_outputs;
   uint32_t                   audio_inputs_count;
   uint32_t                   audio_outputs_count;
   Pointer<const wclap_input_events_t>  in_events;
   Pointer<const wclap_output_events_t> out_events;
};
struct wclap_plugin_descriptor {
   wclap_version_t wclap_version;
   Pointer<const char> id;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> manual_url;
   Pointer<const char> support_url;
   Pointer<const char> version;
   Pointer<const char> description;
   Pointer<const char> Pointer<const> features;
};
struct wclap_plugin {
   Pointer<const wclap_plugin_descriptor_t> desc;

   Pointer<void> plugin_data;
   Function<bool,Pointer<const struct wclap_plugin> plugin> init;
   Function<void,Pointer<const struct wclap_plugin> plugin> destroy;
   Function<bool,Pointer<const struct wclap_plugin> plugin,
                            double                    sample_rate,
                            uint32_t                  min_frames_count,
                            uint32_t                  max_frames_count> activate;
   Function<void,Pointer<const struct wclap_plugin> plugin> deactivate;
   Function<bool,Pointer<const struct wclap_plugin> plugin> start_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> stop_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> reset;
   Function<wclap_process_status,Pointer<const struct wclap_plugin> plugin,
                                          Pointer<const wclap_process_t>     process> process;
   Function<Pointer<const void> ,Pointer<const struct wclap_plugin> plugin, Pointer<const char> id> get_extension;
   Function<void,Pointer<const struct wclap_plugin> plugin> on_main_thread;
};
struct wclap_mini_curve_display_curve_hints {
   double x_min;
   double x_max;
   double y_min;
   double y_max;

};
struct wclap_mini_curve_display_curve_data {
   int32_t curve_kind;
   Pointer<uint16_t> values;
   uint32_t  values_count;
};
struct wclap_plugin_mini_curve_display {
   Function<uint32_t,Pointer<const wclap_plugin_t> plugin> get_curve_count;
   Function<uint32_t,Pointer<const wclap_plugin_t>                  plugin,
                              Pointer<wclap_mini_curve_display_curve_data_t> curves,
                              uint32_t                              curves_size> render;
   Function<void,Pointer<const wclap_plugin_t> plugin, bool is_observed> set_observed;
   Function<bool,Pointer<const wclap_plugin_t> plugin,
                                 uint32_t             curve_index,
                                 Pointer<char>                x_name,
                                 Pointer<char>                y_name,
                                 uint32_t             name_capacity> get_axis_name;
};
struct wclap_host_mini_curve_display {
   Function<bool,Pointer<const wclap_host_t>                     host,
                             uint32_t                               kind,
                             Pointer<wclap_mini_curve_display_curve_hints_t> hints> get_hints;
   Function<void,Pointer<const wclap_host_t> host, bool is_dynamic> set_dynamic;
   Function<void,Pointer<const wclap_host_t> host, uint32_t flags> changed;
};
struct wclap_color {
   uint8_t alpha;
   uint8_t red;
   uint8_t green;
   uint8_t blue;
};
struct wclap_version {
   uint32_t major;
   uint32_t minor;
   uint32_t revision;
};
struct wclap_host {
   wclap_version_t wclap_version;

   Pointer<void> host_data;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> version;
   Function<Pointer<const void> ,Pointer<const struct wclap_host> host, Pointer<const char> extension_id> get_extension;
   Function<void,Pointer<const struct wclap_host> host> request_restart;
   Function<void,Pointer<const struct wclap_host> host> request_process;
   Function<void,Pointer<const struct wclap_host> host> request_callback;
};
typedef int64_t wclap_beattime;
typedef int64_t wclap_sectime;
typedef uint32_t wclap_id;
typedef int32_t wclap_note_expression;
struct wclap_event_header {
   uint32_t size;
   uint32_t time;
   uint16_t space_id;
   uint16_t type;
   uint32_t flags;
};
struct wclap_event_note {
   wclap_event_header_t header;

   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;
   double  velocity;
};
struct wclap_event_note_expression {
   wclap_event_header_t header;

   wclap_note_expression expression_id;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_value {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_mod {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double amount;
};
struct wclap_event_param_gesture {
   wclap_event_header_t header;
   wclap_id param_id;
};
struct wclap_event_transport {
   wclap_event_header_t header;

   uint32_t flags;

   wclap_beattime song_pos_beats;
   wclap_sectime  song_pos_seconds;

   double tempo;
   double tempo_inc;

   wclap_beattime loop_start_beats;
   wclap_beattime loop_end_beats;
   wclap_sectime  loop_start_seconds;
   wclap_sectime  loop_end_seconds;

   wclap_beattime bar_start;
   int32_t       bar_number;

   uint16_t tsig_num;
   uint16_t tsig_denom;
};
struct wclap_event_midi {
   wclap_event_header_t header;

   uint16_t port_index;
   uint8_t  data[3];
};
struct wclap_event_midi_sysex {
   wclap_event_header_t header;

   uint16_t       port_index;
   Pointer<const uint8_t> buffer;
   uint32_t       size;
};
struct wclap_event_midi2 {
   wclap_event_header_t header;

   uint16_t port_index;
   uint32_t data[4];
};
struct wclap_input_events {
   Pointer<void> ctx;
   Function<uint32_t,Pointer<const struct wclap_input_events> list> size;
   Function<Pointer<const wclap_event_header_t> ,Pointer<const struct wclap_input_events> list, uint32_t index> get;
};
struct wclap_output_events {
   Pointer<void> ctx;
   Function<bool,Pointer<const struct wclap_output_events> list,
                            Pointer<const wclap_event_header_t>       event> try_push;
};
struct wclap_audio_buffer {
   Pointer<Pointer<float>>  data32;
   Pointer<Pointer<double>> data64;
   uint32_t channel_count;
   uint32_t latency;
   uint64_t constant_mask;
};
typedef int32_t wclap_process_status;
struct wclap_process {
   int64_t steady_time;
   uint32_t frames_count;
   Pointer<const wclap_event_transport_t> transport;
   Pointer<const wclap_audio_buffer_t> audio_inputs;
   Pointer<wclap_audio_buffer_t>       audio_outputs;
   uint32_t                   audio_inputs_count;
   uint32_t                   audio_outputs_count;
   Pointer<const wclap_input_events_t>  in_events;
   Pointer<const wclap_output_events_t> out_events;
};
struct wclap_plugin_descriptor {
   wclap_version_t wclap_version;
   Pointer<const char> id;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> manual_url;
   Pointer<const char> support_url;
   Pointer<const char> version;
   Pointer<const char> description;
   Pointer<const char> Pointer<const> features;
};
struct wclap_plugin {
   Pointer<const wclap_plugin_descriptor_t> desc;

   Pointer<void> plugin_data;
   Function<bool,Pointer<const struct wclap_plugin> plugin> init;
   Function<void,Pointer<const struct wclap_plugin> plugin> destroy;
   Function<bool,Pointer<const struct wclap_plugin> plugin,
                            double                    sample_rate,
                            uint32_t                  min_frames_count,
                            uint32_t                  max_frames_count> activate;
   Function<void,Pointer<const struct wclap_plugin> plugin> deactivate;
   Function<bool,Pointer<const struct wclap_plugin> plugin> start_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> stop_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> reset;
   Function<wclap_process_status,Pointer<const struct wclap_plugin> plugin,
                                          Pointer<const wclap_process_t>     process> process;
   Function<Pointer<const void> ,Pointer<const struct wclap_plugin> plugin, Pointer<const char> id> get_extension;
   Function<void,Pointer<const struct wclap_plugin> plugin> on_main_thread;
};
struct wclap_project_location_element {
   uint64_t flags;
   uint32_t kind;
   uint32_t track_kind;
   uint32_t index;
   char id[CLAP_PATH_SIZE];
   char name[CLAP_NAME_SIZE];
   wclap_color_t color;
};
struct wclap_plugin_project_location {
   Function<void,Pointer<const wclap_plugin_t>                  plugin,
                       Pointer<const wclap_project_location_element_t> path,
                       uint32_t                              num_elements> set;
};
struct wclap_version {
   uint32_t major;
   uint32_t minor;
   uint32_t revision;
};
struct wclap_host {
   wclap_version_t wclap_version;

   Pointer<void> host_data;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> version;
   Function<Pointer<const void> ,Pointer<const struct wclap_host> host, Pointer<const char> extension_id> get_extension;
   Function<void,Pointer<const struct wclap_host> host> request_restart;
   Function<void,Pointer<const struct wclap_host> host> request_process;
   Function<void,Pointer<const struct wclap_host> host> request_callback;
};
typedef int64_t wclap_beattime;
typedef int64_t wclap_sectime;
typedef uint32_t wclap_id;
typedef int32_t wclap_note_expression;
struct wclap_event_header {
   uint32_t size;
   uint32_t time;
   uint16_t space_id;
   uint16_t type;
   uint32_t flags;
};
struct wclap_event_note {
   wclap_event_header_t header;

   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;
   double  velocity;
};
struct wclap_event_note_expression {
   wclap_event_header_t header;

   wclap_note_expression expression_id;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_value {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_mod {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double amount;
};
struct wclap_event_param_gesture {
   wclap_event_header_t header;
   wclap_id param_id;
};
struct wclap_event_transport {
   wclap_event_header_t header;

   uint32_t flags;

   wclap_beattime song_pos_beats;
   wclap_sectime  song_pos_seconds;

   double tempo;
   double tempo_inc;

   wclap_beattime loop_start_beats;
   wclap_beattime loop_end_beats;
   wclap_sectime  loop_start_seconds;
   wclap_sectime  loop_end_seconds;

   wclap_beattime bar_start;
   int32_t       bar_number;

   uint16_t tsig_num;
   uint16_t tsig_denom;
};
struct wclap_event_midi {
   wclap_event_header_t header;

   uint16_t port_index;
   uint8_t  data[3];
};
struct wclap_event_midi_sysex {
   wclap_event_header_t header;

   uint16_t       port_index;
   Pointer<const uint8_t> buffer;
   uint32_t       size;
};
struct wclap_event_midi2 {
   wclap_event_header_t header;

   uint16_t port_index;
   uint32_t data[4];
};
struct wclap_input_events {
   Pointer<void> ctx;
   Function<uint32_t,Pointer<const struct wclap_input_events> list> size;
   Function<Pointer<const wclap_event_header_t> ,Pointer<const struct wclap_input_events> list, uint32_t index> get;
};
struct wclap_output_events {
   Pointer<void> ctx;
   Function<bool,Pointer<const struct wclap_output_events> list,
                            Pointer<const wclap_event_header_t>       event> try_push;
};
struct wclap_audio_buffer {
   Pointer<Pointer<float>>  data32;
   Pointer<Pointer<double>> data64;
   uint32_t channel_count;
   uint32_t latency;
   uint64_t constant_mask;
};
typedef int32_t wclap_process_status;
struct wclap_process {
   int64_t steady_time;
   uint32_t frames_count;
   Pointer<const wclap_event_transport_t> transport;
   Pointer<const wclap_audio_buffer_t> audio_inputs;
   Pointer<wclap_audio_buffer_t>       audio_outputs;
   uint32_t                   audio_inputs_count;
   uint32_t                   audio_outputs_count;
   Pointer<const wclap_input_events_t>  in_events;
   Pointer<const wclap_output_events_t> out_events;
};
struct wclap_plugin_descriptor {
   wclap_version_t wclap_version;
   Pointer<const char> id;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> manual_url;
   Pointer<const char> support_url;
   Pointer<const char> version;
   Pointer<const char> description;
   Pointer<const char> Pointer<const> features;
};
struct wclap_plugin {
   Pointer<const wclap_plugin_descriptor_t> desc;

   Pointer<void> plugin_data;
   Function<bool,Pointer<const struct wclap_plugin> plugin> init;
   Function<void,Pointer<const struct wclap_plugin> plugin> destroy;
   Function<bool,Pointer<const struct wclap_plugin> plugin,
                            double                    sample_rate,
                            uint32_t                  min_frames_count,
                            uint32_t                  max_frames_count> activate;
   Function<void,Pointer<const struct wclap_plugin> plugin> deactivate;
   Function<bool,Pointer<const struct wclap_plugin> plugin> start_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> stop_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> reset;
   Function<wclap_process_status,Pointer<const struct wclap_plugin> plugin,
                                          Pointer<const wclap_process_t>     process> process;
   Function<Pointer<const void> ,Pointer<const struct wclap_plugin> plugin, Pointer<const char> id> get_extension;
   Function<void,Pointer<const struct wclap_plugin> plugin> on_main_thread;
};
struct wclap_plugin_resource_directory {
   Function<void,Pointer<const wclap_plugin_t> plugin, Pointer<const char> path, bool is_shared> set_directory;
   Function<void,Pointer<const wclap_plugin_t> plugin, bool all> collect;
   Function<uint32_t,Pointer<const wclap_plugin_t> plugin> get_files_count;
   Function<int32_t,Pointer<const wclap_plugin_t> plugin,
                                    uint32_t             index,
                                    Pointer<char>                path,
                                    uint32_t             path_size> get_file_path;
};
struct wclap_host_resource_directory {
   Function<bool,Pointer<const wclap_host_t> host, bool is_shared> request_directory;
   Function<void,Pointer<const wclap_host_t> host, bool is_shared> release_directory;
};
struct wclap_version {
   uint32_t major;
   uint32_t minor;
   uint32_t revision;
};
struct wclap_host {
   wclap_version_t wclap_version;

   Pointer<void> host_data;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> version;
   Function<Pointer<const void> ,Pointer<const struct wclap_host> host, Pointer<const char> extension_id> get_extension;
   Function<void,Pointer<const struct wclap_host> host> request_restart;
   Function<void,Pointer<const struct wclap_host> host> request_process;
   Function<void,Pointer<const struct wclap_host> host> request_callback;
};
typedef int64_t wclap_beattime;
typedef int64_t wclap_sectime;
typedef uint32_t wclap_id;
typedef int32_t wclap_note_expression;
struct wclap_event_header {
   uint32_t size;
   uint32_t time;
   uint16_t space_id;
   uint16_t type;
   uint32_t flags;
};
struct wclap_event_note {
   wclap_event_header_t header;

   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;
   double  velocity;
};
struct wclap_event_note_expression {
   wclap_event_header_t header;

   wclap_note_expression expression_id;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_value {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_mod {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double amount;
};
struct wclap_event_param_gesture {
   wclap_event_header_t header;
   wclap_id param_id;
};
struct wclap_event_transport {
   wclap_event_header_t header;

   uint32_t flags;

   wclap_beattime song_pos_beats;
   wclap_sectime  song_pos_seconds;

   double tempo;
   double tempo_inc;

   wclap_beattime loop_start_beats;
   wclap_beattime loop_end_beats;
   wclap_sectime  loop_start_seconds;
   wclap_sectime  loop_end_seconds;

   wclap_beattime bar_start;
   int32_t       bar_number;

   uint16_t tsig_num;
   uint16_t tsig_denom;
};
struct wclap_event_midi {
   wclap_event_header_t header;

   uint16_t port_index;
   uint8_t  data[3];
};
struct wclap_event_midi_sysex {
   wclap_event_header_t header;

   uint16_t       port_index;
   Pointer<const uint8_t> buffer;
   uint32_t       size;
};
struct wclap_event_midi2 {
   wclap_event_header_t header;

   uint16_t port_index;
   uint32_t data[4];
};
struct wclap_input_events {
   Pointer<void> ctx;
   Function<uint32_t,Pointer<const struct wclap_input_events> list> size;
   Function<Pointer<const wclap_event_header_t> ,Pointer<const struct wclap_input_events> list, uint32_t index> get;
};
struct wclap_output_events {
   Pointer<void> ctx;
   Function<bool,Pointer<const struct wclap_output_events> list,
                            Pointer<const wclap_event_header_t>       event> try_push;
};
struct wclap_audio_buffer {
   Pointer<Pointer<float>>  data32;
   Pointer<Pointer<double>> data64;
   uint32_t channel_count;
   uint32_t latency;
   uint64_t constant_mask;
};
typedef int32_t wclap_process_status;
struct wclap_process {
   int64_t steady_time;
   uint32_t frames_count;
   Pointer<const wclap_event_transport_t> transport;
   Pointer<const wclap_audio_buffer_t> audio_inputs;
   Pointer<wclap_audio_buffer_t>       audio_outputs;
   uint32_t                   audio_inputs_count;
   uint32_t                   audio_outputs_count;
   Pointer<const wclap_input_events_t>  in_events;
   Pointer<const wclap_output_events_t> out_events;
};
struct wclap_plugin_descriptor {
   wclap_version_t wclap_version;
   Pointer<const char> id;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> manual_url;
   Pointer<const char> support_url;
   Pointer<const char> version;
   Pointer<const char> description;
   Pointer<const char> Pointer<const> features;
};
struct wclap_plugin {
   Pointer<const wclap_plugin_descriptor_t> desc;

   Pointer<void> plugin_data;
   Function<bool,Pointer<const struct wclap_plugin> plugin> init;
   Function<void,Pointer<const struct wclap_plugin> plugin> destroy;
   Function<bool,Pointer<const struct wclap_plugin> plugin,
                            double                    sample_rate,
                            uint32_t                  min_frames_count,
                            uint32_t                  max_frames_count> activate;
   Function<void,Pointer<const struct wclap_plugin> plugin> deactivate;
   Function<bool,Pointer<const struct wclap_plugin> plugin> start_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> stop_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> reset;
   Function<wclap_process_status,Pointer<const struct wclap_plugin> plugin,
                                          Pointer<const wclap_process_t>     process> process;
   Function<Pointer<const void> ,Pointer<const struct wclap_plugin> plugin, Pointer<const char> id> get_extension;
   Function<void,Pointer<const struct wclap_plugin> plugin> on_main_thread;
};
struct wclap_host_scratch_memory {
   Function<bool,Pointer<const wclap_host_t> host,
                           uint32_t           scratch_size_bytes,
                           uint32_t           max_concurrency_hint> reserve;
   Function<Pointer<void> ,Pointer<const wclap_host_t> host> access;
};
struct wclap_version {
   uint32_t major;
   uint32_t minor;
   uint32_t revision;
};
struct wclap_host {
   wclap_version_t wclap_version;

   Pointer<void> host_data;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> version;
   Function<Pointer<const void> ,Pointer<const struct wclap_host> host, Pointer<const char> extension_id> get_extension;
   Function<void,Pointer<const struct wclap_host> host> request_restart;
   Function<void,Pointer<const struct wclap_host> host> request_process;
   Function<void,Pointer<const struct wclap_host> host> request_callback;
};
typedef int64_t wclap_beattime;
typedef int64_t wclap_sectime;
typedef uint32_t wclap_id;
typedef int32_t wclap_note_expression;
struct wclap_event_header {
   uint32_t size;
   uint32_t time;
   uint16_t space_id;
   uint16_t type;
   uint32_t flags;
};
struct wclap_event_note {
   wclap_event_header_t header;

   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;
   double  velocity;
};
struct wclap_event_note_expression {
   wclap_event_header_t header;

   wclap_note_expression expression_id;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_value {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_mod {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double amount;
};
struct wclap_event_param_gesture {
   wclap_event_header_t header;
   wclap_id param_id;
};
struct wclap_event_transport {
   wclap_event_header_t header;

   uint32_t flags;

   wclap_beattime song_pos_beats;
   wclap_sectime  song_pos_seconds;

   double tempo;
   double tempo_inc;

   wclap_beattime loop_start_beats;
   wclap_beattime loop_end_beats;
   wclap_sectime  loop_start_seconds;
   wclap_sectime  loop_end_seconds;

   wclap_beattime bar_start;
   int32_t       bar_number;

   uint16_t tsig_num;
   uint16_t tsig_denom;
};
struct wclap_event_midi {
   wclap_event_header_t header;

   uint16_t port_index;
   uint8_t  data[3];
};
struct wclap_event_midi_sysex {
   wclap_event_header_t header;

   uint16_t       port_index;
   Pointer<const uint8_t> buffer;
   uint32_t       size;
};
struct wclap_event_midi2 {
   wclap_event_header_t header;

   uint16_t port_index;
   uint32_t data[4];
};
struct wclap_input_events {
   Pointer<void> ctx;
   Function<uint32_t,Pointer<const struct wclap_input_events> list> size;
   Function<Pointer<const wclap_event_header_t> ,Pointer<const struct wclap_input_events> list, uint32_t index> get;
};
struct wclap_output_events {
   Pointer<void> ctx;
   Function<bool,Pointer<const struct wclap_output_events> list,
                            Pointer<const wclap_event_header_t>       event> try_push;
};
struct wclap_audio_buffer {
   Pointer<Pointer<float>>  data32;
   Pointer<Pointer<double>> data64;
   uint32_t channel_count;
   uint32_t latency;
   uint64_t constant_mask;
};
typedef int32_t wclap_process_status;
struct wclap_process {
   int64_t steady_time;
   uint32_t frames_count;
   Pointer<const wclap_event_transport_t> transport;
   Pointer<const wclap_audio_buffer_t> audio_inputs;
   Pointer<wclap_audio_buffer_t>       audio_outputs;
   uint32_t                   audio_inputs_count;
   uint32_t                   audio_outputs_count;
   Pointer<const wclap_input_events_t>  in_events;
   Pointer<const wclap_output_events_t> out_events;
};
struct wclap_plugin_descriptor {
   wclap_version_t wclap_version;
   Pointer<const char> id;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> manual_url;
   Pointer<const char> support_url;
   Pointer<const char> version;
   Pointer<const char> description;
   Pointer<const char> Pointer<const> features;
};
struct wclap_plugin {
   Pointer<const wclap_plugin_descriptor_t> desc;

   Pointer<void> plugin_data;
   Function<bool,Pointer<const struct wclap_plugin> plugin> init;
   Function<void,Pointer<const struct wclap_plugin> plugin> destroy;
   Function<bool,Pointer<const struct wclap_plugin> plugin,
                            double                    sample_rate,
                            uint32_t                  min_frames_count,
                            uint32_t                  max_frames_count> activate;
   Function<void,Pointer<const struct wclap_plugin> plugin> deactivate;
   Function<bool,Pointer<const struct wclap_plugin> plugin> start_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> stop_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> reset;
   Function<wclap_process_status,Pointer<const struct wclap_plugin> plugin,
                                          Pointer<const wclap_process_t>     process> process;
   Function<Pointer<const void> ,Pointer<const struct wclap_plugin> plugin, Pointer<const char> id> get_extension;
   Function<void,Pointer<const struct wclap_plugin> plugin> on_main_thread;
};
struct wclap_host_transport_control {
   Function<void,Pointer<const wclap_host_t> host> request_start;
   Function<void,Pointer<const wclap_host_t> host> request_stop;
   Function<void,Pointer<const wclap_host_t> host> request_continue;
   Function<void,Pointer<const wclap_host_t> host> request_pause;
   Function<void,Pointer<const wclap_host_t> host> request_toggle_play;
   Function<void,Pointer<const wclap_host_t> host, wclap_beattime position> request_jump;
   Function<void,Pointer<const wclap_host_t> host,
                                       wclap_beattime      start,
                                       wclap_beattime      duration> request_loop_region;
   Function<void,Pointer<const wclap_host_t> host> request_toggle_loop;
   Function<void,Pointer<const wclap_host_t> host, bool is_enabled> request_enable_loop;
   Function<void,Pointer<const wclap_host_t> host, bool is_recording> request_record;
   Function<void,Pointer<const wclap_host_t> host> request_toggle_record;
};
struct wclap_version {
   uint32_t major;
   uint32_t minor;
   uint32_t revision;
};
struct wclap_host {
   wclap_version_t wclap_version;

   Pointer<void> host_data;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> version;
   Function<Pointer<const void> ,Pointer<const struct wclap_host> host, Pointer<const char> extension_id> get_extension;
   Function<void,Pointer<const struct wclap_host> host> request_restart;
   Function<void,Pointer<const struct wclap_host> host> request_process;
   Function<void,Pointer<const struct wclap_host> host> request_callback;
};
typedef int64_t wclap_beattime;
typedef int64_t wclap_sectime;
typedef uint32_t wclap_id;
typedef int32_t wclap_note_expression;
struct wclap_event_header {
   uint32_t size;
   uint32_t time;
   uint16_t space_id;
   uint16_t type;
   uint32_t flags;
};
struct wclap_event_note {
   wclap_event_header_t header;

   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;
   double  velocity;
};
struct wclap_event_note_expression {
   wclap_event_header_t header;

   wclap_note_expression expression_id;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_value {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_mod {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double amount;
};
struct wclap_event_param_gesture {
   wclap_event_header_t header;
   wclap_id param_id;
};
struct wclap_event_transport {
   wclap_event_header_t header;

   uint32_t flags;

   wclap_beattime song_pos_beats;
   wclap_sectime  song_pos_seconds;

   double tempo;
   double tempo_inc;

   wclap_beattime loop_start_beats;
   wclap_beattime loop_end_beats;
   wclap_sectime  loop_start_seconds;
   wclap_sectime  loop_end_seconds;

   wclap_beattime bar_start;
   int32_t       bar_number;

   uint16_t tsig_num;
   uint16_t tsig_denom;
};
struct wclap_event_midi {
   wclap_event_header_t header;

   uint16_t port_index;
   uint8_t  data[3];
};
struct wclap_event_midi_sysex {
   wclap_event_header_t header;

   uint16_t       port_index;
   Pointer<const uint8_t> buffer;
   uint32_t       size;
};
struct wclap_event_midi2 {
   wclap_event_header_t header;

   uint16_t port_index;
   uint32_t data[4];
};
struct wclap_input_events {
   Pointer<void> ctx;
   Function<uint32_t,Pointer<const struct wclap_input_events> list> size;
   Function<Pointer<const wclap_event_header_t> ,Pointer<const struct wclap_input_events> list, uint32_t index> get;
};
struct wclap_output_events {
   Pointer<void> ctx;
   Function<bool,Pointer<const struct wclap_output_events> list,
                            Pointer<const wclap_event_header_t>       event> try_push;
};
struct wclap_audio_buffer {
   Pointer<Pointer<float>>  data32;
   Pointer<Pointer<double>> data64;
   uint32_t channel_count;
   uint32_t latency;
   uint64_t constant_mask;
};
typedef int32_t wclap_process_status;
struct wclap_process {
   int64_t steady_time;
   uint32_t frames_count;
   Pointer<const wclap_event_transport_t> transport;
   Pointer<const wclap_audio_buffer_t> audio_inputs;
   Pointer<wclap_audio_buffer_t>       audio_outputs;
   uint32_t                   audio_inputs_count;
   uint32_t                   audio_outputs_count;
   Pointer<const wclap_input_events_t>  in_events;
   Pointer<const wclap_output_events_t> out_events;
};
struct wclap_plugin_descriptor {
   wclap_version_t wclap_version;
   Pointer<const char> id;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> manual_url;
   Pointer<const char> support_url;
   Pointer<const char> version;
   Pointer<const char> description;
   Pointer<const char> Pointer<const> features;
};
struct wclap_plugin {
   Pointer<const wclap_plugin_descriptor_t> desc;

   Pointer<void> plugin_data;
   Function<bool,Pointer<const struct wclap_plugin> plugin> init;
   Function<void,Pointer<const struct wclap_plugin> plugin> destroy;
   Function<bool,Pointer<const struct wclap_plugin> plugin,
                            double                    sample_rate,
                            uint32_t                  min_frames_count,
                            uint32_t                  max_frames_count> activate;
   Function<void,Pointer<const struct wclap_plugin> plugin> deactivate;
   Function<bool,Pointer<const struct wclap_plugin> plugin> start_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> stop_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> reset;
   Function<wclap_process_status,Pointer<const struct wclap_plugin> plugin,
                                          Pointer<const wclap_process_t>     process> process;
   Function<Pointer<const void> ,Pointer<const struct wclap_plugin> plugin, Pointer<const char> id> get_extension;
   Function<void,Pointer<const struct wclap_plugin> plugin> on_main_thread;
};
typedef int64_t wclap_beattime;
typedef int64_t wclap_sectime;
typedef uint32_t wclap_id;
typedef int32_t wclap_note_expression;
struct wclap_event_header {
   uint32_t size;
   uint32_t time;
   uint16_t space_id;
   uint16_t type;
   uint32_t flags;
};
struct wclap_event_note {
   wclap_event_header_t header;

   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;
   double  velocity;
};
struct wclap_event_note_expression {
   wclap_event_header_t header;

   wclap_note_expression expression_id;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_value {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_mod {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double amount;
};
struct wclap_event_param_gesture {
   wclap_event_header_t header;
   wclap_id param_id;
};
struct wclap_event_transport {
   wclap_event_header_t header;

   uint32_t flags;

   wclap_beattime song_pos_beats;
   wclap_sectime  song_pos_seconds;

   double tempo;
   double tempo_inc;

   wclap_beattime loop_start_beats;
   wclap_beattime loop_end_beats;
   wclap_sectime  loop_start_seconds;
   wclap_sectime  loop_end_seconds;

   wclap_beattime bar_start;
   int32_t       bar_number;

   uint16_t tsig_num;
   uint16_t tsig_denom;
};
struct wclap_event_midi {
   wclap_event_header_t header;

   uint16_t port_index;
   uint8_t  data[3];
};
struct wclap_event_midi_sysex {
   wclap_event_header_t header;

   uint16_t       port_index;
   Pointer<const uint8_t> buffer;
   uint32_t       size;
};
struct wclap_event_midi2 {
   wclap_event_header_t header;

   uint16_t port_index;
   uint32_t data[4];
};
struct wclap_input_events {
   Pointer<void> ctx;
   Function<uint32_t,Pointer<const struct wclap_input_events> list> size;
   Function<Pointer<const wclap_event_header_t> ,Pointer<const struct wclap_input_events> list, uint32_t index> get;
};
struct wclap_output_events {
   Pointer<void> ctx;
   Function<bool,Pointer<const struct wclap_output_events> list,
                            Pointer<const wclap_event_header_t>       event> try_push;
};
typedef uint32_t wclap_trigger_info_flags;
typedef uint32_t wclap_trigger_rescan_flags;
typedef uint32_t wclap_trigger_clear_flags;
struct wclap_event_trigger {
   wclap_event_header_t header;
   wclap_id trigger_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;
};
struct wclap_trigger_info {
   wclap_id id;

   wclap_trigger_info_flags flags;
   Pointer<void> cookie;
   char name[CLAP_NAME_SIZE];
   char module[CLAP_PATH_SIZE];
};
struct wclap_plugin_triggers {
   Function<uint32_t,Pointer<const wclap_plugin_t> plugin> count;
   Function<bool,Pointer<const wclap_plugin_t> plugin,
                            uint32_t             index,
                            Pointer<wclap_trigger_info_t> trigger_info> get_info;
};
struct wclap_host_triggers {
   Function<void,Pointer<const wclap_host_t> host, wclap_trigger_rescan_flags flags> rescan;
   Function<void,Pointer<const wclap_host_t>       host,
                         wclap_id                  trigger_id,
                         wclap_trigger_clear_flags flags> clear;
};
struct wclap_version {
   uint32_t major;
   uint32_t minor;
   uint32_t revision;
};
struct wclap_host {
   wclap_version_t wclap_version;

   Pointer<void> host_data;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> version;
   Function<Pointer<const void> ,Pointer<const struct wclap_host> host, Pointer<const char> extension_id> get_extension;
   Function<void,Pointer<const struct wclap_host> host> request_restart;
   Function<void,Pointer<const struct wclap_host> host> request_process;
   Function<void,Pointer<const struct wclap_host> host> request_callback;
};
typedef int64_t wclap_beattime;
typedef int64_t wclap_sectime;
typedef uint32_t wclap_id;
typedef int32_t wclap_note_expression;
struct wclap_event_header {
   uint32_t size;
   uint32_t time;
   uint16_t space_id;
   uint16_t type;
   uint32_t flags;
};
struct wclap_event_note {
   wclap_event_header_t header;

   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;
   double  velocity;
};
struct wclap_event_note_expression {
   wclap_event_header_t header;

   wclap_note_expression expression_id;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_value {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_mod {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double amount;
};
struct wclap_event_param_gesture {
   wclap_event_header_t header;
   wclap_id param_id;
};
struct wclap_event_transport {
   wclap_event_header_t header;

   uint32_t flags;

   wclap_beattime song_pos_beats;
   wclap_sectime  song_pos_seconds;

   double tempo;
   double tempo_inc;

   wclap_beattime loop_start_beats;
   wclap_beattime loop_end_beats;
   wclap_sectime  loop_start_seconds;
   wclap_sectime  loop_end_seconds;

   wclap_beattime bar_start;
   int32_t       bar_number;

   uint16_t tsig_num;
   uint16_t tsig_denom;
};
struct wclap_event_midi {
   wclap_event_header_t header;

   uint16_t port_index;
   uint8_t  data[3];
};
struct wclap_event_midi_sysex {
   wclap_event_header_t header;

   uint16_t       port_index;
   Pointer<const uint8_t> buffer;
   uint32_t       size;
};
struct wclap_event_midi2 {
   wclap_event_header_t header;

   uint16_t port_index;
   uint32_t data[4];
};
struct wclap_input_events {
   Pointer<void> ctx;
   Function<uint32_t,Pointer<const struct wclap_input_events> list> size;
   Function<Pointer<const wclap_event_header_t> ,Pointer<const struct wclap_input_events> list, uint32_t index> get;
};
struct wclap_output_events {
   Pointer<void> ctx;
   Function<bool,Pointer<const struct wclap_output_events> list,
                            Pointer<const wclap_event_header_t>       event> try_push;
};
struct wclap_audio_buffer {
   Pointer<Pointer<float>>  data32;
   Pointer<Pointer<double>> data64;
   uint32_t channel_count;
   uint32_t latency;
   uint64_t constant_mask;
};
typedef int32_t wclap_process_status;
struct wclap_process {
   int64_t steady_time;
   uint32_t frames_count;
   Pointer<const wclap_event_transport_t> transport;
   Pointer<const wclap_audio_buffer_t> audio_inputs;
   Pointer<wclap_audio_buffer_t>       audio_outputs;
   uint32_t                   audio_inputs_count;
   uint32_t                   audio_outputs_count;
   Pointer<const wclap_input_events_t>  in_events;
   Pointer<const wclap_output_events_t> out_events;
};
struct wclap_plugin_descriptor {
   wclap_version_t wclap_version;
   Pointer<const char> id;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> manual_url;
   Pointer<const char> support_url;
   Pointer<const char> version;
   Pointer<const char> description;
   Pointer<const char> Pointer<const> features;
};
struct wclap_plugin {
   Pointer<const wclap_plugin_descriptor_t> desc;

   Pointer<void> plugin_data;
   Function<bool,Pointer<const struct wclap_plugin> plugin> init;
   Function<void,Pointer<const struct wclap_plugin> plugin> destroy;
   Function<bool,Pointer<const struct wclap_plugin> plugin,
                            double                    sample_rate,
                            uint32_t                  min_frames_count,
                            uint32_t                  max_frames_count> activate;
   Function<void,Pointer<const struct wclap_plugin> plugin> deactivate;
   Function<bool,Pointer<const struct wclap_plugin> plugin> start_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> stop_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> reset;
   Function<wclap_process_status,Pointer<const struct wclap_plugin> plugin,
                                          Pointer<const wclap_process_t>     process> process;
   Function<Pointer<const void> ,Pointer<const struct wclap_plugin> plugin, Pointer<const char> id> get_extension;
   Function<void,Pointer<const struct wclap_plugin> plugin> on_main_thread;
};
typedef int64_t wclap_beattime;
typedef int64_t wclap_sectime;
typedef uint32_t wclap_id;
typedef int32_t wclap_note_expression;
struct wclap_event_header {
   uint32_t size;
   uint32_t time;
   uint16_t space_id;
   uint16_t type;
   uint32_t flags;
};
struct wclap_event_note {
   wclap_event_header_t header;

   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;
   double  velocity;
};
struct wclap_event_note_expression {
   wclap_event_header_t header;

   wclap_note_expression expression_id;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_value {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_mod {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double amount;
};
struct wclap_event_param_gesture {
   wclap_event_header_t header;
   wclap_id param_id;
};
struct wclap_event_transport {
   wclap_event_header_t header;

   uint32_t flags;

   wclap_beattime song_pos_beats;
   wclap_sectime  song_pos_seconds;

   double tempo;
   double tempo_inc;

   wclap_beattime loop_start_beats;
   wclap_beattime loop_end_beats;
   wclap_sectime  loop_start_seconds;
   wclap_sectime  loop_end_seconds;

   wclap_beattime bar_start;
   int32_t       bar_number;

   uint16_t tsig_num;
   uint16_t tsig_denom;
};
struct wclap_event_midi {
   wclap_event_header_t header;

   uint16_t port_index;
   uint8_t  data[3];
};
struct wclap_event_midi_sysex {
   wclap_event_header_t header;

   uint16_t       port_index;
   Pointer<const uint8_t> buffer;
   uint32_t       size;
};
struct wclap_event_midi2 {
   wclap_event_header_t header;

   uint16_t port_index;
   uint32_t data[4];
};
struct wclap_input_events {
   Pointer<void> ctx;
   Function<uint32_t,Pointer<const struct wclap_input_events> list> size;
   Function<Pointer<const wclap_event_header_t> ,Pointer<const struct wclap_input_events> list, uint32_t index> get;
};
struct wclap_output_events {
   Pointer<void> ctx;
   Function<bool,Pointer<const struct wclap_output_events> list,
                            Pointer<const wclap_event_header_t>       event> try_push;
};
struct wclap_event_tuning {
   wclap_event_header_t header;

   int16_t port_index;
   int16_t channel;
   wclap_id tunning_id;
};
struct wclap_tuning_info {
   wclap_id tuning_id;
   char    name[CLAP_NAME_SIZE];
   bool    is_dynamic;
};
struct wclap_plugin_tuning {
   Function<void,Pointer<const wclap_plugin_t> plugin> changed;
};
struct wclap_host_tuning {
   Function<double,Pointer<const wclap_host_t> host,
                                  wclap_id            tuning_id,
                                  int32_t            channel,
                                  int32_t            key,
                                  uint32_t           sample_offset> get_relative;
   Function<bool,Pointer<const wclap_host_t> host,
                               wclap_id            tuning_id,
                               int32_t            channel,
                               int32_t            key> should_play;
   Function<uint32_t,Pointer<const wclap_host_t> host> get_tuning_count;
   Function<bool,Pointer<const wclap_host_t>  host,
                            uint32_t            tuning_index,
                            Pointer<wclap_tuning_info_t> info> get_info;
};
struct wclap_version {
   uint32_t major;
   uint32_t minor;
   uint32_t revision;
};
struct wclap_host {
   wclap_version_t wclap_version;

   Pointer<void> host_data;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> version;
   Function<Pointer<const void> ,Pointer<const struct wclap_host> host, Pointer<const char> extension_id> get_extension;
   Function<void,Pointer<const struct wclap_host> host> request_restart;
   Function<void,Pointer<const struct wclap_host> host> request_process;
   Function<void,Pointer<const struct wclap_host> host> request_callback;
};
typedef int64_t wclap_beattime;
typedef int64_t wclap_sectime;
typedef uint32_t wclap_id;
typedef int32_t wclap_note_expression;
struct wclap_event_header {
   uint32_t size;
   uint32_t time;
   uint16_t space_id;
   uint16_t type;
   uint32_t flags;
};
struct wclap_event_note {
   wclap_event_header_t header;

   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;
   double  velocity;
};
struct wclap_event_note_expression {
   wclap_event_header_t header;

   wclap_note_expression expression_id;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_value {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_mod {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double amount;
};
struct wclap_event_param_gesture {
   wclap_event_header_t header;
   wclap_id param_id;
};
struct wclap_event_transport {
   wclap_event_header_t header;

   uint32_t flags;

   wclap_beattime song_pos_beats;
   wclap_sectime  song_pos_seconds;

   double tempo;
   double tempo_inc;

   wclap_beattime loop_start_beats;
   wclap_beattime loop_end_beats;
   wclap_sectime  loop_start_seconds;
   wclap_sectime  loop_end_seconds;

   wclap_beattime bar_start;
   int32_t       bar_number;

   uint16_t tsig_num;
   uint16_t tsig_denom;
};
struct wclap_event_midi {
   wclap_event_header_t header;

   uint16_t port_index;
   uint8_t  data[3];
};
struct wclap_event_midi_sysex {
   wclap_event_header_t header;

   uint16_t       port_index;
   Pointer<const uint8_t> buffer;
   uint32_t       size;
};
struct wclap_event_midi2 {
   wclap_event_header_t header;

   uint16_t port_index;
   uint32_t data[4];
};
struct wclap_input_events {
   Pointer<void> ctx;
   Function<uint32_t,Pointer<const struct wclap_input_events> list> size;
   Function<Pointer<const wclap_event_header_t> ,Pointer<const struct wclap_input_events> list, uint32_t index> get;
};
struct wclap_output_events {
   Pointer<void> ctx;
   Function<bool,Pointer<const struct wclap_output_events> list,
                            Pointer<const wclap_event_header_t>       event> try_push;
};
struct wclap_audio_buffer {
   Pointer<Pointer<float>>  data32;
   Pointer<Pointer<double>> data64;
   uint32_t channel_count;
   uint32_t latency;
   uint64_t constant_mask;
};
typedef int32_t wclap_process_status;
struct wclap_process {
   int64_t steady_time;
   uint32_t frames_count;
   Pointer<const wclap_event_transport_t> transport;
   Pointer<const wclap_audio_buffer_t> audio_inputs;
   Pointer<wclap_audio_buffer_t>       audio_outputs;
   uint32_t                   audio_inputs_count;
   uint32_t                   audio_outputs_count;
   Pointer<const wclap_input_events_t>  in_events;
   Pointer<const wclap_output_events_t> out_events;
};
struct wclap_plugin_descriptor {
   wclap_version_t wclap_version;
   Pointer<const char> id;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> manual_url;
   Pointer<const char> support_url;
   Pointer<const char> version;
   Pointer<const char> description;
   Pointer<const char> Pointer<const> features;
};
struct wclap_plugin {
   Pointer<const wclap_plugin_descriptor_t> desc;

   Pointer<void> plugin_data;
   Function<bool,Pointer<const struct wclap_plugin> plugin> init;
   Function<void,Pointer<const struct wclap_plugin> plugin> destroy;
   Function<bool,Pointer<const struct wclap_plugin> plugin,
                            double                    sample_rate,
                            uint32_t                  min_frames_count,
                            uint32_t                  max_frames_count> activate;
   Function<void,Pointer<const struct wclap_plugin> plugin> deactivate;
   Function<bool,Pointer<const struct wclap_plugin> plugin> start_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> stop_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> reset;
   Function<wclap_process_status,Pointer<const struct wclap_plugin> plugin,
                                          Pointer<const wclap_process_t>     process> process;
   Function<Pointer<const void> ,Pointer<const struct wclap_plugin> plugin, Pointer<const char> id> get_extension;
   Function<void,Pointer<const struct wclap_plugin> plugin> on_main_thread;
};
struct wclap_istream {
   Pointer<void> ctx;
   Function<int64_t,Pointer<const struct wclap_istream> stream, Pointer<void> buffer, uint64_t size> read;
};
struct wclap_ostream {
   Pointer<void> ctx;
   Function<int64_t,Pointer<const struct wclap_ostream> stream, Pointer<const void> buffer, uint64_t size> write;
};
struct wclap_undo_delta_properties {
   bool has_delta;
   bool are_deltas_persistent;
   wclap_id format_version;
};
struct wclap_plugin_undo_delta {
   Function<void,Pointer<const wclap_plugin_t>          plugin,
                                        Pointer<wclap_undo_delta_properties_t> properties> get_delta_properties;
   Function<bool,Pointer<const wclap_plugin_t> plugin,
                                                wclap_id              format_version> can_use_delta_format_version;
   Function<bool,Pointer<const wclap_plugin_t> plugin,
                        wclap_id              format_version,
                        Pointer<const void>          delta,
                        size_t               delta_size> undo;
   Function<bool,Pointer<const wclap_plugin_t> plugin,
                        wclap_id              format_version,
                        Pointer<const void>          delta,
                        size_t               delta_size> redo;
};
struct wclap_plugin_undo_context {
   Function<void,Pointer<const wclap_plugin_t> plugin, bool can_undo> set_can_undo;
   Function<void,Pointer<const wclap_plugin_t> plugin, bool can_redo> set_can_redo;
   Function<void,Pointer<const wclap_plugin_t> plugin, Pointer<const char> name> set_undo_name;
   Function<void,Pointer<const wclap_plugin_t> plugin, Pointer<const char> name> set_redo_name;
};
struct wclap_host_undo {
   Function<void,Pointer<const wclap_host_t> host> begin_change;
   Function<void,Pointer<const wclap_host_t> host> cancel_change;
   Function<void,Pointer<const wclap_host_t> host,
                               Pointer<const char>        name,
                               Pointer<const void>        delta,
                               size_t             delta_size,
                               bool               delta_can_undo> change_made;
   Function<void,Pointer<const wclap_host_t> host> request_undo;
   Function<void,Pointer<const wclap_host_t> host> request_redo;
   Function<void,Pointer<const wclap_host_t> host, bool is_subscribed> set_wants_context_updates;
};
struct wclap_audio_buffer {
   Pointer<Pointer<float>>  data32;
   Pointer<Pointer<double>> data64;
   uint32_t channel_count;
   uint32_t latency;
   uint64_t constant_mask;
};
struct wclap_version {
   uint32_t major;
   uint32_t minor;
   uint32_t revision;
};
struct wclap_plugin_entry {
   wclap_version_t wclap_version;
   Function<bool,Pointer<const char> plugin_path> init;
   Function<void,void> deinit;
   Function<Pointer<const void> ,Pointer<const char> factory_id> get_factory;
};
struct wclap_version {
   uint32_t major;
   uint32_t minor;
   uint32_t revision;
};
struct wclap_host {
   wclap_version_t wclap_version;

   Pointer<void> host_data;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> version;
   Function<Pointer<const void> ,Pointer<const struct wclap_host> host, Pointer<const char> extension_id> get_extension;
   Function<void,Pointer<const struct wclap_host> host> request_restart;
   Function<void,Pointer<const struct wclap_host> host> request_process;
   Function<void,Pointer<const struct wclap_host> host> request_callback;
};
typedef int64_t wclap_beattime;
typedef int64_t wclap_sectime;
typedef uint32_t wclap_id;
typedef int32_t wclap_note_expression;
struct wclap_event_header {
   uint32_t size;
   uint32_t time;
   uint16_t space_id;
   uint16_t type;
   uint32_t flags;
};
struct wclap_event_note {
   wclap_event_header_t header;

   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;
   double  velocity;
};
struct wclap_event_note_expression {
   wclap_event_header_t header;

   wclap_note_expression expression_id;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_value {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_mod {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double amount;
};
struct wclap_event_param_gesture {
   wclap_event_header_t header;
   wclap_id param_id;
};
struct wclap_event_transport {
   wclap_event_header_t header;

   uint32_t flags;

   wclap_beattime song_pos_beats;
   wclap_sectime  song_pos_seconds;

   double tempo;
   double tempo_inc;

   wclap_beattime loop_start_beats;
   wclap_beattime loop_end_beats;
   wclap_sectime  loop_start_seconds;
   wclap_sectime  loop_end_seconds;

   wclap_beattime bar_start;
   int32_t       bar_number;

   uint16_t tsig_num;
   uint16_t tsig_denom;
};
struct wclap_event_midi {
   wclap_event_header_t header;

   uint16_t port_index;
   uint8_t  data[3];
};
struct wclap_event_midi_sysex {
   wclap_event_header_t header;

   uint16_t       port_index;
   Pointer<const uint8_t> buffer;
   uint32_t       size;
};
struct wclap_event_midi2 {
   wclap_event_header_t header;

   uint16_t port_index;
   uint32_t data[4];
};
struct wclap_input_events {
   Pointer<void> ctx;
   Function<uint32_t,Pointer<const struct wclap_input_events> list> size;
   Function<Pointer<const wclap_event_header_t> ,Pointer<const struct wclap_input_events> list, uint32_t index> get;
};
struct wclap_output_events {
   Pointer<void> ctx;
   Function<bool,Pointer<const struct wclap_output_events> list,
                            Pointer<const wclap_event_header_t>       event> try_push;
};
struct wclap_audio_buffer {
   Pointer<Pointer<float>>  data32;
   Pointer<Pointer<double>> data64;
   uint32_t channel_count;
   uint32_t latency;
   uint64_t constant_mask;
};
typedef int32_t wclap_process_status;
struct wclap_process {
   int64_t steady_time;
   uint32_t frames_count;
   Pointer<const wclap_event_transport_t> transport;
   Pointer<const wclap_audio_buffer_t> audio_inputs;
   Pointer<wclap_audio_buffer_t>       audio_outputs;
   uint32_t                   audio_inputs_count;
   uint32_t                   audio_outputs_count;
   Pointer<const wclap_input_events_t>  in_events;
   Pointer<const wclap_output_events_t> out_events;
};
struct wclap_plugin_descriptor {
   wclap_version_t wclap_version;
   Pointer<const char> id;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> manual_url;
   Pointer<const char> support_url;
   Pointer<const char> version;
   Pointer<const char> description;
   Pointer<const char> Pointer<const> features;
};
struct wclap_plugin {
   Pointer<const wclap_plugin_descriptor_t> desc;

   Pointer<void> plugin_data;
   Function<bool,Pointer<const struct wclap_plugin> plugin> init;
   Function<void,Pointer<const struct wclap_plugin> plugin> destroy;
   Function<bool,Pointer<const struct wclap_plugin> plugin,
                            double                    sample_rate,
                            uint32_t                  min_frames_count,
                            uint32_t                  max_frames_count> activate;
   Function<void,Pointer<const struct wclap_plugin> plugin> deactivate;
   Function<bool,Pointer<const struct wclap_plugin> plugin> start_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> stop_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> reset;
   Function<wclap_process_status,Pointer<const struct wclap_plugin> plugin,
                                          Pointer<const wclap_process_t>     process> process;
   Function<Pointer<const void> ,Pointer<const struct wclap_plugin> plugin, Pointer<const char> id> get_extension;
   Function<void,Pointer<const struct wclap_plugin> plugin> on_main_thread;
};
struct wclap_plugin_factory {
   Function<uint32_t,Pointer<const struct wclap_plugin_factory> factory> get_plugin_count;
   Function<Pointer<const wclap_plugin_descriptor_t> ,
      Pointer<const struct wclap_plugin_factory> factory, uint32_t index> get_plugin_descriptor;
   Function<Pointer<const wclap_plugin_t> ,Pointer<const struct wclap_plugin_factory> factory,
                                                  Pointer<const wclap_host_t>                host,
                                                  Pointer<const char>                       plugin_id> create_plugin;
};
typedef uint64_t wclap_timestamp;
struct wclap_version {
   uint32_t major;
   uint32_t minor;
   uint32_t revision;
};
struct wclap_universal_plugin_id {
   Pointer<const char> abi;
   Pointer<const char> id;
};
struct wclap_preset_discovery_metadata_receiver {
   Pointer<void> receiver_data;
   Function<void,Pointer<const struct wclap_preset_discovery_metadata_receiver> receiver,
                            int32_t                                               os_error,
                            Pointer<const char>                                           error_message> on_error;
   Function<bool,Pointer<const struct wclap_preset_discovery_metadata_receiver> receiver,
                                Pointer<const char>                                           name,
                                Pointer<const char>                                           load_key> begin_preset;
   Function<void,Pointer<const struct wclap_preset_discovery_metadata_receiver> receiver,
                                 Pointer<const wclap_universal_plugin_id_t>                     plugin_id> add_plugin_id;
   Function<void,Pointer<const struct wclap_preset_discovery_metadata_receiver> receiver,
                                    Pointer<const char> soundpack_id> set_soundpack_id;
   Function<void,Pointer<const struct wclap_preset_discovery_metadata_receiver> receiver,
                             uint32_t                                              flags> set_flags;
   Function<void,Pointer<const struct wclap_preset_discovery_metadata_receiver> receiver,
                               Pointer<const char>                                           creator> add_creator;
   Function<void,Pointer<const struct wclap_preset_discovery_metadata_receiver> receiver,
                                   Pointer<const char> description> set_description;
   Function<void,Pointer<const struct wclap_preset_discovery_metadata_receiver> receiver,
                                  wclap_timestamp creation_time,
                                  wclap_timestamp modification_time> set_timestamps;
   Function<void,Pointer<const struct wclap_preset_discovery_metadata_receiver> receiver,
                               Pointer<const char>                                           feature> add_feature;
   Function<void,Pointer<const struct wclap_preset_discovery_metadata_receiver> receiver,
                                  Pointer<const char>                                           key,
                                  Pointer<const char>                                           value> add_extra_info;
};
struct wclap_preset_discovery_filetype {
   Pointer<const char> name;
   Pointer<const char> description;
   Pointer<const char> file_extension;
};
struct wclap_preset_discovery_location {
   uint32_t    flags;
   Pointer<const char> name;
   uint32_t    kind;
   Pointer<const char> location;
};
struct wclap_preset_discovery_soundpack {
   uint32_t       flags;
   Pointer<const char>    id;
   Pointer<const char>    name;
   Pointer<const char>    description;
   Pointer<const char>    homepage_url;
   Pointer<const char>    vendor;
   Pointer<const char>    image_path;
   wclap_timestamp release_timestamp;
};
struct wclap_preset_discovery_provider_descriptor {
   wclap_version_t wclap_version;
   Pointer<const char>    id;
   Pointer<const char>    name;
   Pointer<const char>    vendor;
};
struct wclap_preset_discovery_provider {
   Pointer<const wclap_preset_discovery_provider_descriptor_t> desc;

   Pointer<void> provider_data;
   Function<bool,Pointer<const struct wclap_preset_discovery_provider> provider> init;
   Function<void,Pointer<const struct wclap_preset_discovery_provider> provider> destroy;
   Function<bool,Pointer<const struct wclap_preset_discovery_provider>     provider,
                                uint32_t                                         location_kind,
                                Pointer<const char>                                      location,
                                Pointer<const wclap_preset_discovery_metadata_receiver_t> metadata_receiver> get_metadata;
   Function<Pointer<const void> ,Pointer<const struct wclap_preset_discovery_provider> provider,
                                         Pointer<const char>                                  extension_id> get_extension;
};
struct wclap_preset_discovery_indexer {
   wclap_version_t wclap_version;
   Pointer<const char>    name;
   Pointer<const char>    vendor;
   Pointer<const char>    url;
   Pointer<const char> version;

   Pointer<void> indexer_data;
   Function<bool,Pointer<const struct wclap_preset_discovery_indexer> indexer,
                                    Pointer<const wclap_preset_discovery_filetype_t>     filetype> declare_filetype;
   Function<bool,Pointer<const struct wclap_preset_discovery_indexer> indexer,
                                    Pointer<const wclap_preset_discovery_location_t>     location> declare_location;
   Function<bool,Pointer<const struct wclap_preset_discovery_indexer> indexer,
                                     Pointer<const wclap_preset_discovery_soundpack_t>    soundpack> declare_soundpack;
   Function<Pointer<const void> ,Pointer<const struct wclap_preset_discovery_indexer> indexer,
                                         Pointer<const char>                                 extension_id> get_extension;
};
struct wclap_preset_discovery_factory {
   Function<uint32_t,Pointer<const struct wclap_preset_discovery_factory> factory> count;
   Function<Pointer<const wclap_preset_discovery_provider_descriptor_t> ,
      Pointer<const struct wclap_preset_discovery_factory> factory, uint32_t index> get_descriptor;
   Function<Pointer<const wclap_preset_discovery_provider_t> ,
      Pointer<const struct wclap_preset_discovery_factory> factory,
      Pointer<const wclap_preset_discovery_indexer_t>      indexer,
      Pointer<const char>                                 provider_id> create;
};
struct wclap_version {
   uint32_t major;
   uint32_t minor;
   uint32_t revision;
};
struct wclap_host {
   wclap_version_t wclap_version;

   Pointer<void> host_data;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> version;
   Function<Pointer<const void> ,Pointer<const struct wclap_host> host, Pointer<const char> extension_id> get_extension;
   Function<void,Pointer<const struct wclap_host> host> request_restart;
   Function<void,Pointer<const struct wclap_host> host> request_process;
   Function<void,Pointer<const struct wclap_host> host> request_callback;
};
typedef int64_t wclap_beattime;
typedef int64_t wclap_sectime;
typedef uint32_t wclap_id;
typedef int32_t wclap_note_expression;
struct wclap_event_header {
   uint32_t size;
   uint32_t time;
   uint16_t space_id;
   uint16_t type;
   uint32_t flags;
};
struct wclap_event_note {
   wclap_event_header_t header;

   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;
   double  velocity;
};
struct wclap_event_note_expression {
   wclap_event_header_t header;

   wclap_note_expression expression_id;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_value {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_mod {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double amount;
};
struct wclap_event_param_gesture {
   wclap_event_header_t header;
   wclap_id param_id;
};
struct wclap_event_transport {
   wclap_event_header_t header;

   uint32_t flags;

   wclap_beattime song_pos_beats;
   wclap_sectime  song_pos_seconds;

   double tempo;
   double tempo_inc;

   wclap_beattime loop_start_beats;
   wclap_beattime loop_end_beats;
   wclap_sectime  loop_start_seconds;
   wclap_sectime  loop_end_seconds;

   wclap_beattime bar_start;
   int32_t       bar_number;

   uint16_t tsig_num;
   uint16_t tsig_denom;
};
struct wclap_event_midi {
   wclap_event_header_t header;

   uint16_t port_index;
   uint8_t  data[3];
};
struct wclap_event_midi_sysex {
   wclap_event_header_t header;

   uint16_t       port_index;
   Pointer<const uint8_t> buffer;
   uint32_t       size;
};
struct wclap_event_midi2 {
   wclap_event_header_t header;

   uint16_t port_index;
   uint32_t data[4];
};
struct wclap_input_events {
   Pointer<void> ctx;
   Function<uint32_t,Pointer<const struct wclap_input_events> list> size;
   Function<Pointer<const wclap_event_header_t> ,Pointer<const struct wclap_input_events> list, uint32_t index> get;
};
struct wclap_output_events {
   Pointer<void> ctx;
   Function<bool,Pointer<const struct wclap_output_events> list,
                            Pointer<const wclap_event_header_t>       event> try_push;
};
struct wclap_audio_buffer {
   Pointer<Pointer<float>>  data32;
   Pointer<Pointer<double>> data64;
   uint32_t channel_count;
   uint32_t latency;
   uint64_t constant_mask;
};
typedef int32_t wclap_process_status;
struct wclap_process {
   int64_t steady_time;
   uint32_t frames_count;
   Pointer<const wclap_event_transport_t> transport;
   Pointer<const wclap_audio_buffer_t> audio_inputs;
   Pointer<wclap_audio_buffer_t>       audio_outputs;
   uint32_t                   audio_inputs_count;
   uint32_t                   audio_outputs_count;
   Pointer<const wclap_input_events_t>  in_events;
   Pointer<const wclap_output_events_t> out_events;
};
struct wclap_plugin_descriptor {
   wclap_version_t wclap_version;
   Pointer<const char> id;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> manual_url;
   Pointer<const char> support_url;
   Pointer<const char> version;
   Pointer<const char> description;
   Pointer<const char> Pointer<const> features;
};
struct wclap_plugin {
   Pointer<const wclap_plugin_descriptor_t> desc;

   Pointer<void> plugin_data;
   Function<bool,Pointer<const struct wclap_plugin> plugin> init;
   Function<void,Pointer<const struct wclap_plugin> plugin> destroy;
   Function<bool,Pointer<const struct wclap_plugin> plugin,
                            double                    sample_rate,
                            uint32_t                  min_frames_count,
                            uint32_t                  max_frames_count> activate;
   Function<void,Pointer<const struct wclap_plugin> plugin> deactivate;
   Function<bool,Pointer<const struct wclap_plugin> plugin> start_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> stop_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> reset;
   Function<wclap_process_status,Pointer<const struct wclap_plugin> plugin,
                                          Pointer<const wclap_process_t>     process> process;
   Function<Pointer<const void> ,Pointer<const struct wclap_plugin> plugin, Pointer<const char> id> get_extension;
   Function<void,Pointer<const struct wclap_plugin> plugin> on_main_thread;
};
struct wclap_version {
   uint32_t major;
   uint32_t minor;
   uint32_t revision;
};
struct wclap_host {
   wclap_version_t wclap_version;

   Pointer<void> host_data;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> version;
   Function<Pointer<const void> ,Pointer<const struct wclap_host> host, Pointer<const char> extension_id> get_extension;
   Function<void,Pointer<const struct wclap_host> host> request_restart;
   Function<void,Pointer<const struct wclap_host> host> request_process;
   Function<void,Pointer<const struct wclap_host> host> request_callback;
};
struct wclap_universal_plugin_id {
   Pointer<const char> abi;
   Pointer<const char> id;
};
struct wclap_version {
   uint32_t major;
   uint32_t minor;
   uint32_t revision;
};
struct wclap_host {
   wclap_version_t wclap_version;

   Pointer<void> host_data;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> version;
   Function<Pointer<const void> ,Pointer<const struct wclap_host> host, Pointer<const char> extension_id> get_extension;
   Function<void,Pointer<const struct wclap_host> host> request_restart;
   Function<void,Pointer<const struct wclap_host> host> request_process;
   Function<void,Pointer<const struct wclap_host> host> request_callback;
};
typedef int64_t wclap_beattime;
typedef int64_t wclap_sectime;
typedef uint32_t wclap_id;
typedef int32_t wclap_note_expression;
struct wclap_event_header {
   uint32_t size;
   uint32_t time;
   uint16_t space_id;
   uint16_t type;
   uint32_t flags;
};
struct wclap_event_note {
   wclap_event_header_t header;

   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;
   double  velocity;
};
struct wclap_event_note_expression {
   wclap_event_header_t header;

   wclap_note_expression expression_id;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_value {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_mod {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double amount;
};
struct wclap_event_param_gesture {
   wclap_event_header_t header;
   wclap_id param_id;
};
struct wclap_event_transport {
   wclap_event_header_t header;

   uint32_t flags;

   wclap_beattime song_pos_beats;
   wclap_sectime  song_pos_seconds;

   double tempo;
   double tempo_inc;

   wclap_beattime loop_start_beats;
   wclap_beattime loop_end_beats;
   wclap_sectime  loop_start_seconds;
   wclap_sectime  loop_end_seconds;

   wclap_beattime bar_start;
   int32_t       bar_number;

   uint16_t tsig_num;
   uint16_t tsig_denom;
};
struct wclap_event_midi {
   wclap_event_header_t header;

   uint16_t port_index;
   uint8_t  data[3];
};
struct wclap_event_midi_sysex {
   wclap_event_header_t header;

   uint16_t       port_index;
   Pointer<const uint8_t> buffer;
   uint32_t       size;
};
struct wclap_event_midi2 {
   wclap_event_header_t header;

   uint16_t port_index;
   uint32_t data[4];
};
struct wclap_input_events {
   Pointer<void> ctx;
   Function<uint32_t,Pointer<const struct wclap_input_events> list> size;
   Function<Pointer<const wclap_event_header_t> ,Pointer<const struct wclap_input_events> list, uint32_t index> get;
};
struct wclap_output_events {
   Pointer<void> ctx;
   Function<bool,Pointer<const struct wclap_output_events> list,
                            Pointer<const wclap_event_header_t>       event> try_push;
};
struct wclap_audio_buffer {
   Pointer<Pointer<float>>  data32;
   Pointer<Pointer<double>> data64;
   uint32_t channel_count;
   uint32_t latency;
   uint64_t constant_mask;
};
typedef int32_t wclap_process_status;
struct wclap_process {
   int64_t steady_time;
   uint32_t frames_count;
   Pointer<const wclap_event_transport_t> transport;
   Pointer<const wclap_audio_buffer_t> audio_inputs;
   Pointer<wclap_audio_buffer_t>       audio_outputs;
   uint32_t                   audio_inputs_count;
   uint32_t                   audio_outputs_count;
   Pointer<const wclap_input_events_t>  in_events;
   Pointer<const wclap_output_events_t> out_events;
};
struct wclap_plugin_descriptor {
   wclap_version_t wclap_version;
   Pointer<const char> id;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> manual_url;
   Pointer<const char> support_url;
   Pointer<const char> version;
   Pointer<const char> description;
   Pointer<const char> Pointer<const> features;
};
struct wclap_plugin {
   Pointer<const wclap_plugin_descriptor_t> desc;

   Pointer<void> plugin_data;
   Function<bool,Pointer<const struct wclap_plugin> plugin> init;
   Function<void,Pointer<const struct wclap_plugin> plugin> destroy;
   Function<bool,Pointer<const struct wclap_plugin> plugin,
                            double                    sample_rate,
                            uint32_t                  min_frames_count,
                            uint32_t                  max_frames_count> activate;
   Function<void,Pointer<const struct wclap_plugin> plugin> deactivate;
   Function<bool,Pointer<const struct wclap_plugin> plugin> start_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> stop_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> reset;
   Function<wclap_process_status,Pointer<const struct wclap_plugin> plugin,
                                          Pointer<const wclap_process_t>     process> process;
   Function<Pointer<const void> ,Pointer<const struct wclap_plugin> plugin, Pointer<const char> id> get_extension;
   Function<void,Pointer<const struct wclap_plugin> plugin> on_main_thread;
};
struct wclap_ambisonic_config {
   uint32_t ordering;
   uint32_t normalization;
};
struct wclap_plugin_ambisonic {
   Function<bool,Pointer<const wclap_plugin_t>           plugin,
                                       Pointer<const wclap_ambisonic_config_t> config> is_config_supported;
   Function<bool,Pointer<const wclap_plugin_t>     plugin,
                              bool                     is_input,
                              uint32_t                 port_index,
                              Pointer<wclap_ambisonic_config_t> config> get_config;

};
struct wclap_host_ambisonic {
   Function<void,Pointer<const wclap_host_t> host> changed;
};
struct wclap_version {
   uint32_t major;
   uint32_t minor;
   uint32_t revision;
};
struct wclap_host {
   wclap_version_t wclap_version;

   Pointer<void> host_data;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> version;
   Function<Pointer<const void> ,Pointer<const struct wclap_host> host, Pointer<const char> extension_id> get_extension;
   Function<void,Pointer<const struct wclap_host> host> request_restart;
   Function<void,Pointer<const struct wclap_host> host> request_process;
   Function<void,Pointer<const struct wclap_host> host> request_callback;
};
typedef int64_t wclap_beattime;
typedef int64_t wclap_sectime;
typedef uint32_t wclap_id;
typedef int32_t wclap_note_expression;
struct wclap_event_header {
   uint32_t size;
   uint32_t time;
   uint16_t space_id;
   uint16_t type;
   uint32_t flags;
};
struct wclap_event_note {
   wclap_event_header_t header;

   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;
   double  velocity;
};
struct wclap_event_note_expression {
   wclap_event_header_t header;

   wclap_note_expression expression_id;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_value {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_mod {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double amount;
};
struct wclap_event_param_gesture {
   wclap_event_header_t header;
   wclap_id param_id;
};
struct wclap_event_transport {
   wclap_event_header_t header;

   uint32_t flags;

   wclap_beattime song_pos_beats;
   wclap_sectime  song_pos_seconds;

   double tempo;
   double tempo_inc;

   wclap_beattime loop_start_beats;
   wclap_beattime loop_end_beats;
   wclap_sectime  loop_start_seconds;
   wclap_sectime  loop_end_seconds;

   wclap_beattime bar_start;
   int32_t       bar_number;

   uint16_t tsig_num;
   uint16_t tsig_denom;
};
struct wclap_event_midi {
   wclap_event_header_t header;

   uint16_t port_index;
   uint8_t  data[3];
};
struct wclap_event_midi_sysex {
   wclap_event_header_t header;

   uint16_t       port_index;
   Pointer<const uint8_t> buffer;
   uint32_t       size;
};
struct wclap_event_midi2 {
   wclap_event_header_t header;

   uint16_t port_index;
   uint32_t data[4];
};
struct wclap_input_events {
   Pointer<void> ctx;
   Function<uint32_t,Pointer<const struct wclap_input_events> list> size;
   Function<Pointer<const wclap_event_header_t> ,Pointer<const struct wclap_input_events> list, uint32_t index> get;
};
struct wclap_output_events {
   Pointer<void> ctx;
   Function<bool,Pointer<const struct wclap_output_events> list,
                            Pointer<const wclap_event_header_t>       event> try_push;
};
struct wclap_audio_buffer {
   Pointer<Pointer<float>>  data32;
   Pointer<Pointer<double>> data64;
   uint32_t channel_count;
   uint32_t latency;
   uint64_t constant_mask;
};
typedef int32_t wclap_process_status;
struct wclap_process {
   int64_t steady_time;
   uint32_t frames_count;
   Pointer<const wclap_event_transport_t> transport;
   Pointer<const wclap_audio_buffer_t> audio_inputs;
   Pointer<wclap_audio_buffer_t>       audio_outputs;
   uint32_t                   audio_inputs_count;
   uint32_t                   audio_outputs_count;
   Pointer<const wclap_input_events_t>  in_events;
   Pointer<const wclap_output_events_t> out_events;
};
struct wclap_plugin_descriptor {
   wclap_version_t wclap_version;
   Pointer<const char> id;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> manual_url;
   Pointer<const char> support_url;
   Pointer<const char> version;
   Pointer<const char> description;
   Pointer<const char> Pointer<const> features;
};
struct wclap_plugin {
   Pointer<const wclap_plugin_descriptor_t> desc;

   Pointer<void> plugin_data;
   Function<bool,Pointer<const struct wclap_plugin> plugin> init;
   Function<void,Pointer<const struct wclap_plugin> plugin> destroy;
   Function<bool,Pointer<const struct wclap_plugin> plugin,
                            double                    sample_rate,
                            uint32_t                  min_frames_count,
                            uint32_t                  max_frames_count> activate;
   Function<void,Pointer<const struct wclap_plugin> plugin> deactivate;
   Function<bool,Pointer<const struct wclap_plugin> plugin> start_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> stop_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> reset;
   Function<wclap_process_status,Pointer<const struct wclap_plugin> plugin,
                                          Pointer<const wclap_process_t>     process> process;
   Function<Pointer<const void> ,Pointer<const struct wclap_plugin> plugin, Pointer<const char> id> get_extension;
   Function<void,Pointer<const struct wclap_plugin> plugin> on_main_thread;
};
struct wclap_plugin_audio_ports_activation {
   Function<bool,Pointer<const wclap_plugin_t> plugin> can_activate_while_processing;
   Function<bool,Pointer<const wclap_plugin_t> plugin,
                              bool                 is_input,
                              uint32_t             port_index,
                              bool                 is_active,
                              uint32_t             sample_size> set_active;
};
struct wclap_version {
   uint32_t major;
   uint32_t minor;
   uint32_t revision;
};
struct wclap_host {
   wclap_version_t wclap_version;

   Pointer<void> host_data;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> version;
   Function<Pointer<const void> ,Pointer<const struct wclap_host> host, Pointer<const char> extension_id> get_extension;
   Function<void,Pointer<const struct wclap_host> host> request_restart;
   Function<void,Pointer<const struct wclap_host> host> request_process;
   Function<void,Pointer<const struct wclap_host> host> request_callback;
};
typedef int64_t wclap_beattime;
typedef int64_t wclap_sectime;
typedef uint32_t wclap_id;
typedef int32_t wclap_note_expression;
struct wclap_event_header {
   uint32_t size;
   uint32_t time;
   uint16_t space_id;
   uint16_t type;
   uint32_t flags;
};
struct wclap_event_note {
   wclap_event_header_t header;

   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;
   double  velocity;
};
struct wclap_event_note_expression {
   wclap_event_header_t header;

   wclap_note_expression expression_id;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_value {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_mod {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double amount;
};
struct wclap_event_param_gesture {
   wclap_event_header_t header;
   wclap_id param_id;
};
struct wclap_event_transport {
   wclap_event_header_t header;

   uint32_t flags;

   wclap_beattime song_pos_beats;
   wclap_sectime  song_pos_seconds;

   double tempo;
   double tempo_inc;

   wclap_beattime loop_start_beats;
   wclap_beattime loop_end_beats;
   wclap_sectime  loop_start_seconds;
   wclap_sectime  loop_end_seconds;

   wclap_beattime bar_start;
   int32_t       bar_number;

   uint16_t tsig_num;
   uint16_t tsig_denom;
};
struct wclap_event_midi {
   wclap_event_header_t header;

   uint16_t port_index;
   uint8_t  data[3];
};
struct wclap_event_midi_sysex {
   wclap_event_header_t header;

   uint16_t       port_index;
   Pointer<const uint8_t> buffer;
   uint32_t       size;
};
struct wclap_event_midi2 {
   wclap_event_header_t header;

   uint16_t port_index;
   uint32_t data[4];
};
struct wclap_input_events {
   Pointer<void> ctx;
   Function<uint32_t,Pointer<const struct wclap_input_events> list> size;
   Function<Pointer<const wclap_event_header_t> ,Pointer<const struct wclap_input_events> list, uint32_t index> get;
};
struct wclap_output_events {
   Pointer<void> ctx;
   Function<bool,Pointer<const struct wclap_output_events> list,
                            Pointer<const wclap_event_header_t>       event> try_push;
};
struct wclap_audio_buffer {
   Pointer<Pointer<float>>  data32;
   Pointer<Pointer<double>> data64;
   uint32_t channel_count;
   uint32_t latency;
   uint64_t constant_mask;
};
typedef int32_t wclap_process_status;
struct wclap_process {
   int64_t steady_time;
   uint32_t frames_count;
   Pointer<const wclap_event_transport_t> transport;
   Pointer<const wclap_audio_buffer_t> audio_inputs;
   Pointer<wclap_audio_buffer_t>       audio_outputs;
   uint32_t                   audio_inputs_count;
   uint32_t                   audio_outputs_count;
   Pointer<const wclap_input_events_t>  in_events;
   Pointer<const wclap_output_events_t> out_events;
};
struct wclap_plugin_descriptor {
   wclap_version_t wclap_version;
   Pointer<const char> id;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> manual_url;
   Pointer<const char> support_url;
   Pointer<const char> version;
   Pointer<const char> description;
   Pointer<const char> Pointer<const> features;
};
struct wclap_plugin {
   Pointer<const wclap_plugin_descriptor_t> desc;

   Pointer<void> plugin_data;
   Function<bool,Pointer<const struct wclap_plugin> plugin> init;
   Function<void,Pointer<const struct wclap_plugin> plugin> destroy;
   Function<bool,Pointer<const struct wclap_plugin> plugin,
                            double                    sample_rate,
                            uint32_t                  min_frames_count,
                            uint32_t                  max_frames_count> activate;
   Function<void,Pointer<const struct wclap_plugin> plugin> deactivate;
   Function<bool,Pointer<const struct wclap_plugin> plugin> start_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> stop_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> reset;
   Function<wclap_process_status,Pointer<const struct wclap_plugin> plugin,
                                          Pointer<const wclap_process_t>     process> process;
   Function<Pointer<const void> ,Pointer<const struct wclap_plugin> plugin, Pointer<const char> id> get_extension;
   Function<void,Pointer<const struct wclap_plugin> plugin> on_main_thread;
};
struct wclap_version {
   uint32_t major;
   uint32_t minor;
   uint32_t revision;
};
struct wclap_host {
   wclap_version_t wclap_version;

   Pointer<void> host_data;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> version;
   Function<Pointer<const void> ,Pointer<const struct wclap_host> host, Pointer<const char> extension_id> get_extension;
   Function<void,Pointer<const struct wclap_host> host> request_restart;
   Function<void,Pointer<const struct wclap_host> host> request_process;
   Function<void,Pointer<const struct wclap_host> host> request_callback;
};
typedef int64_t wclap_beattime;
typedef int64_t wclap_sectime;
typedef uint32_t wclap_id;
typedef int32_t wclap_note_expression;
struct wclap_event_header {
   uint32_t size;
   uint32_t time;
   uint16_t space_id;
   uint16_t type;
   uint32_t flags;
};
struct wclap_event_note {
   wclap_event_header_t header;

   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;
   double  velocity;
};
struct wclap_event_note_expression {
   wclap_event_header_t header;

   wclap_note_expression expression_id;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_value {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_mod {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double amount;
};
struct wclap_event_param_gesture {
   wclap_event_header_t header;
   wclap_id param_id;
};
struct wclap_event_transport {
   wclap_event_header_t header;

   uint32_t flags;

   wclap_beattime song_pos_beats;
   wclap_sectime  song_pos_seconds;

   double tempo;
   double tempo_inc;

   wclap_beattime loop_start_beats;
   wclap_beattime loop_end_beats;
   wclap_sectime  loop_start_seconds;
   wclap_sectime  loop_end_seconds;

   wclap_beattime bar_start;
   int32_t       bar_number;

   uint16_t tsig_num;
   uint16_t tsig_denom;
};
struct wclap_event_midi {
   wclap_event_header_t header;

   uint16_t port_index;
   uint8_t  data[3];
};
struct wclap_event_midi_sysex {
   wclap_event_header_t header;

   uint16_t       port_index;
   Pointer<const uint8_t> buffer;
   uint32_t       size;
};
struct wclap_event_midi2 {
   wclap_event_header_t header;

   uint16_t port_index;
   uint32_t data[4];
};
struct wclap_input_events {
   Pointer<void> ctx;
   Function<uint32_t,Pointer<const struct wclap_input_events> list> size;
   Function<Pointer<const wclap_event_header_t> ,Pointer<const struct wclap_input_events> list, uint32_t index> get;
};
struct wclap_output_events {
   Pointer<void> ctx;
   Function<bool,Pointer<const struct wclap_output_events> list,
                            Pointer<const wclap_event_header_t>       event> try_push;
};
struct wclap_audio_buffer {
   Pointer<Pointer<float>>  data32;
   Pointer<Pointer<double>> data64;
   uint32_t channel_count;
   uint32_t latency;
   uint64_t constant_mask;
};
typedef int32_t wclap_process_status;
struct wclap_process {
   int64_t steady_time;
   uint32_t frames_count;
   Pointer<const wclap_event_transport_t> transport;
   Pointer<const wclap_audio_buffer_t> audio_inputs;
   Pointer<wclap_audio_buffer_t>       audio_outputs;
   uint32_t                   audio_inputs_count;
   uint32_t                   audio_outputs_count;
   Pointer<const wclap_input_events_t>  in_events;
   Pointer<const wclap_output_events_t> out_events;
};
struct wclap_plugin_descriptor {
   wclap_version_t wclap_version;
   Pointer<const char> id;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> manual_url;
   Pointer<const char> support_url;
   Pointer<const char> version;
   Pointer<const char> description;
   Pointer<const char> Pointer<const> features;
};
struct wclap_plugin {
   Pointer<const wclap_plugin_descriptor_t> desc;

   Pointer<void> plugin_data;
   Function<bool,Pointer<const struct wclap_plugin> plugin> init;
   Function<void,Pointer<const struct wclap_plugin> plugin> destroy;
   Function<bool,Pointer<const struct wclap_plugin> plugin,
                            double                    sample_rate,
                            uint32_t                  min_frames_count,
                            uint32_t                  max_frames_count> activate;
   Function<void,Pointer<const struct wclap_plugin> plugin> deactivate;
   Function<bool,Pointer<const struct wclap_plugin> plugin> start_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> stop_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> reset;
   Function<wclap_process_status,Pointer<const struct wclap_plugin> plugin,
                                          Pointer<const wclap_process_t>     process> process;
   Function<Pointer<const void> ,Pointer<const struct wclap_plugin> plugin, Pointer<const char> id> get_extension;
   Function<void,Pointer<const struct wclap_plugin> plugin> on_main_thread;
};
struct wclap_audio_port_info {
   wclap_id id;
   char    name[CLAP_NAME_SIZE];

   uint32_t flags;
   uint32_t channel_count;
   Pointer<const char> port_type;
   wclap_id in_place_pair;
};
struct wclap_plugin_audio_ports {
   Function<uint32_t,Pointer<const wclap_plugin_t> plugin, bool is_input> count;
   Function<bool,Pointer<const wclap_plugin_t>    plugin,
                       uint32_t                index,
                       bool                    is_input,
                       Pointer<wclap_audio_port_info_t> info> get;
};
struct wclap_host_audio_ports {
   Function<bool,Pointer<const wclap_host_t> host, uint32_t flag> is_rescan_flag_supported;
   Function<void,Pointer<const wclap_host_t> host, uint32_t flags> rescan;
};
struct wclap_audio_ports_config {
   wclap_id id;
   char    name[CLAP_NAME_SIZE];

   uint32_t input_port_count;
   uint32_t output_port_count;
   bool        has_main_input;
   uint32_t    main_input_channel_count;
   Pointer<const char> main_input_port_type;
   bool        has_main_output;
   uint32_t    main_output_channel_count;
   Pointer<const char> main_output_port_type;
};
struct wclap_plugin_audio_ports_config {
   Function<uint32_t,Pointer<const wclap_plugin_t> plugin> count;
   Function<bool,Pointer<const wclap_plugin_t>       plugin,
                       uint32_t                   index,
                       Pointer<wclap_audio_ports_config_t> config> get;
   Function<bool,Pointer<const wclap_plugin_t> plugin, wclap_id config_id> select;
};
struct wclap_plugin_audio_ports_config_info {
   Function<wclap_id,Pointer<const wclap_plugin_t> plugin> current_config;
   Function<bool,Pointer<const wclap_plugin_t>    plugin,
                       wclap_id                 config_id,
                       uint32_t                port_index,
                       bool                    is_input,
                       Pointer<wclap_audio_port_info_t> info> get;
};
struct wclap_host_audio_ports_config {
   Function<void,Pointer<const wclap_host_t> host> rescan;
};
struct wclap_version {
   uint32_t major;
   uint32_t minor;
   uint32_t revision;
};
struct wclap_host {
   wclap_version_t wclap_version;

   Pointer<void> host_data;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> version;
   Function<Pointer<const void> ,Pointer<const struct wclap_host> host, Pointer<const char> extension_id> get_extension;
   Function<void,Pointer<const struct wclap_host> host> request_restart;
   Function<void,Pointer<const struct wclap_host> host> request_process;
   Function<void,Pointer<const struct wclap_host> host> request_callback;
};
typedef int64_t wclap_beattime;
typedef int64_t wclap_sectime;
typedef uint32_t wclap_id;
typedef int32_t wclap_note_expression;
struct wclap_event_header {
   uint32_t size;
   uint32_t time;
   uint16_t space_id;
   uint16_t type;
   uint32_t flags;
};
struct wclap_event_note {
   wclap_event_header_t header;

   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;
   double  velocity;
};
struct wclap_event_note_expression {
   wclap_event_header_t header;

   wclap_note_expression expression_id;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_value {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_mod {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double amount;
};
struct wclap_event_param_gesture {
   wclap_event_header_t header;
   wclap_id param_id;
};
struct wclap_event_transport {
   wclap_event_header_t header;

   uint32_t flags;

   wclap_beattime song_pos_beats;
   wclap_sectime  song_pos_seconds;

   double tempo;
   double tempo_inc;

   wclap_beattime loop_start_beats;
   wclap_beattime loop_end_beats;
   wclap_sectime  loop_start_seconds;
   wclap_sectime  loop_end_seconds;

   wclap_beattime bar_start;
   int32_t       bar_number;

   uint16_t tsig_num;
   uint16_t tsig_denom;
};
struct wclap_event_midi {
   wclap_event_header_t header;

   uint16_t port_index;
   uint8_t  data[3];
};
struct wclap_event_midi_sysex {
   wclap_event_header_t header;

   uint16_t       port_index;
   Pointer<const uint8_t> buffer;
   uint32_t       size;
};
struct wclap_event_midi2 {
   wclap_event_header_t header;

   uint16_t port_index;
   uint32_t data[4];
};
struct wclap_input_events {
   Pointer<void> ctx;
   Function<uint32_t,Pointer<const struct wclap_input_events> list> size;
   Function<Pointer<const wclap_event_header_t> ,Pointer<const struct wclap_input_events> list, uint32_t index> get;
};
struct wclap_output_events {
   Pointer<void> ctx;
   Function<bool,Pointer<const struct wclap_output_events> list,
                            Pointer<const wclap_event_header_t>       event> try_push;
};
struct wclap_audio_buffer {
   Pointer<Pointer<float>>  data32;
   Pointer<Pointer<double>> data64;
   uint32_t channel_count;
   uint32_t latency;
   uint64_t constant_mask;
};
typedef int32_t wclap_process_status;
struct wclap_process {
   int64_t steady_time;
   uint32_t frames_count;
   Pointer<const wclap_event_transport_t> transport;
   Pointer<const wclap_audio_buffer_t> audio_inputs;
   Pointer<wclap_audio_buffer_t>       audio_outputs;
   uint32_t                   audio_inputs_count;
   uint32_t                   audio_outputs_count;
   Pointer<const wclap_input_events_t>  in_events;
   Pointer<const wclap_output_events_t> out_events;
};
struct wclap_plugin_descriptor {
   wclap_version_t wclap_version;
   Pointer<const char> id;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> manual_url;
   Pointer<const char> support_url;
   Pointer<const char> version;
   Pointer<const char> description;
   Pointer<const char> Pointer<const> features;
};
struct wclap_plugin {
   Pointer<const wclap_plugin_descriptor_t> desc;

   Pointer<void> plugin_data;
   Function<bool,Pointer<const struct wclap_plugin> plugin> init;
   Function<void,Pointer<const struct wclap_plugin> plugin> destroy;
   Function<bool,Pointer<const struct wclap_plugin> plugin,
                            double                    sample_rate,
                            uint32_t                  min_frames_count,
                            uint32_t                  max_frames_count> activate;
   Function<void,Pointer<const struct wclap_plugin> plugin> deactivate;
   Function<bool,Pointer<const struct wclap_plugin> plugin> start_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> stop_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> reset;
   Function<wclap_process_status,Pointer<const struct wclap_plugin> plugin,
                                          Pointer<const wclap_process_t>     process> process;
   Function<Pointer<const void> ,Pointer<const struct wclap_plugin> plugin, Pointer<const char> id> get_extension;
   Function<void,Pointer<const struct wclap_plugin> plugin> on_main_thread;
};
struct wclap_audio_port_info {
   wclap_id id;
   char    name[CLAP_NAME_SIZE];

   uint32_t flags;
   uint32_t channel_count;
   Pointer<const char> port_type;
   wclap_id in_place_pair;
};
struct wclap_plugin_audio_ports {
   Function<uint32_t,Pointer<const wclap_plugin_t> plugin, bool is_input> count;
   Function<bool,Pointer<const wclap_plugin_t>    plugin,
                       uint32_t                index,
                       bool                    is_input,
                       Pointer<wclap_audio_port_info_t> info> get;
};
struct wclap_host_audio_ports {
   Function<bool,Pointer<const wclap_host_t> host, uint32_t flag> is_rescan_flag_supported;
   Function<void,Pointer<const wclap_host_t> host, uint32_t flags> rescan;
};
struct wclap_version {
   uint32_t major;
   uint32_t minor;
   uint32_t revision;
};
struct wclap_host {
   wclap_version_t wclap_version;

   Pointer<void> host_data;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> version;
   Function<Pointer<const void> ,Pointer<const struct wclap_host> host, Pointer<const char> extension_id> get_extension;
   Function<void,Pointer<const struct wclap_host> host> request_restart;
   Function<void,Pointer<const struct wclap_host> host> request_process;
   Function<void,Pointer<const struct wclap_host> host> request_callback;
};
typedef int64_t wclap_beattime;
typedef int64_t wclap_sectime;
typedef uint32_t wclap_id;
typedef int32_t wclap_note_expression;
struct wclap_event_header {
   uint32_t size;
   uint32_t time;
   uint16_t space_id;
   uint16_t type;
   uint32_t flags;
};
struct wclap_event_note {
   wclap_event_header_t header;

   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;
   double  velocity;
};
struct wclap_event_note_expression {
   wclap_event_header_t header;

   wclap_note_expression expression_id;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_value {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_mod {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double amount;
};
struct wclap_event_param_gesture {
   wclap_event_header_t header;
   wclap_id param_id;
};
struct wclap_event_transport {
   wclap_event_header_t header;

   uint32_t flags;

   wclap_beattime song_pos_beats;
   wclap_sectime  song_pos_seconds;

   double tempo;
   double tempo_inc;

   wclap_beattime loop_start_beats;
   wclap_beattime loop_end_beats;
   wclap_sectime  loop_start_seconds;
   wclap_sectime  loop_end_seconds;

   wclap_beattime bar_start;
   int32_t       bar_number;

   uint16_t tsig_num;
   uint16_t tsig_denom;
};
struct wclap_event_midi {
   wclap_event_header_t header;

   uint16_t port_index;
   uint8_t  data[3];
};
struct wclap_event_midi_sysex {
   wclap_event_header_t header;

   uint16_t       port_index;
   Pointer<const uint8_t> buffer;
   uint32_t       size;
};
struct wclap_event_midi2 {
   wclap_event_header_t header;

   uint16_t port_index;
   uint32_t data[4];
};
struct wclap_input_events {
   Pointer<void> ctx;
   Function<uint32_t,Pointer<const struct wclap_input_events> list> size;
   Function<Pointer<const wclap_event_header_t> ,Pointer<const struct wclap_input_events> list, uint32_t index> get;
};
struct wclap_output_events {
   Pointer<void> ctx;
   Function<bool,Pointer<const struct wclap_output_events> list,
                            Pointer<const wclap_event_header_t>       event> try_push;
};
struct wclap_audio_buffer {
   Pointer<Pointer<float>>  data32;
   Pointer<Pointer<double>> data64;
   uint32_t channel_count;
   uint32_t latency;
   uint64_t constant_mask;
};
typedef int32_t wclap_process_status;
struct wclap_process {
   int64_t steady_time;
   uint32_t frames_count;
   Pointer<const wclap_event_transport_t> transport;
   Pointer<const wclap_audio_buffer_t> audio_inputs;
   Pointer<wclap_audio_buffer_t>       audio_outputs;
   uint32_t                   audio_inputs_count;
   uint32_t                   audio_outputs_count;
   Pointer<const wclap_input_events_t>  in_events;
   Pointer<const wclap_output_events_t> out_events;
};
struct wclap_plugin_descriptor {
   wclap_version_t wclap_version;
   Pointer<const char> id;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> manual_url;
   Pointer<const char> support_url;
   Pointer<const char> version;
   Pointer<const char> description;
   Pointer<const char> Pointer<const> features;
};
struct wclap_plugin {
   Pointer<const wclap_plugin_descriptor_t> desc;

   Pointer<void> plugin_data;
   Function<bool,Pointer<const struct wclap_plugin> plugin> init;
   Function<void,Pointer<const struct wclap_plugin> plugin> destroy;
   Function<bool,Pointer<const struct wclap_plugin> plugin,
                            double                    sample_rate,
                            uint32_t                  min_frames_count,
                            uint32_t                  max_frames_count> activate;
   Function<void,Pointer<const struct wclap_plugin> plugin> deactivate;
   Function<bool,Pointer<const struct wclap_plugin> plugin> start_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> stop_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> reset;
   Function<wclap_process_status,Pointer<const struct wclap_plugin> plugin,
                                          Pointer<const wclap_process_t>     process> process;
   Function<Pointer<const void> ,Pointer<const struct wclap_plugin> plugin, Pointer<const char> id> get_extension;
   Function<void,Pointer<const struct wclap_plugin> plugin> on_main_thread;
};
struct wclap_audio_port_info {
   wclap_id id;
   char    name[CLAP_NAME_SIZE];

   uint32_t flags;
   uint32_t channel_count;
   Pointer<const char> port_type;
   wclap_id in_place_pair;
};
struct wclap_plugin_audio_ports {
   Function<uint32_t,Pointer<const wclap_plugin_t> plugin, bool is_input> count;
   Function<bool,Pointer<const wclap_plugin_t>    plugin,
                       uint32_t                index,
                       bool                    is_input,
                       Pointer<wclap_audio_port_info_t> info> get;
};
struct wclap_host_audio_ports {
   Function<bool,Pointer<const wclap_host_t> host, uint32_t flag> is_rescan_flag_supported;
   Function<void,Pointer<const wclap_host_t> host, uint32_t flags> rescan;
};
struct wclap_audio_port_configuration_request {
   bool     is_input;
   uint32_t port_index;
   uint32_t channel_count;
   Pointer<const char> port_type;
   Pointer<const void> port_details;
};
struct wclap_plugin_configurable_audio_ports {
   Function<bool,
      Pointer<const wclap_plugin_t>                                plugin,
      Pointer<const struct wclap_audio_port_configuration_request> requests,
      uint32_t                                            request_count> can_apply_configuration;
   Function<bool,Pointer<const wclap_plugin_t>                                plugin,
                                       Pointer<const struct wclap_audio_port_configuration_request> requests,
                                       uint32_t request_count> apply_configuration;
};
struct wclap_version {
   uint32_t major;
   uint32_t minor;
   uint32_t revision;
};
struct wclap_host {
   wclap_version_t wclap_version;

   Pointer<void> host_data;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> version;
   Function<Pointer<const void> ,Pointer<const struct wclap_host> host, Pointer<const char> extension_id> get_extension;
   Function<void,Pointer<const struct wclap_host> host> request_restart;
   Function<void,Pointer<const struct wclap_host> host> request_process;
   Function<void,Pointer<const struct wclap_host> host> request_callback;
};
typedef int64_t wclap_beattime;
typedef int64_t wclap_sectime;
typedef uint32_t wclap_id;
typedef int32_t wclap_note_expression;
struct wclap_event_header {
   uint32_t size;
   uint32_t time;
   uint16_t space_id;
   uint16_t type;
   uint32_t flags;
};
struct wclap_event_note {
   wclap_event_header_t header;

   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;
   double  velocity;
};
struct wclap_event_note_expression {
   wclap_event_header_t header;

   wclap_note_expression expression_id;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_value {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_mod {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double amount;
};
struct wclap_event_param_gesture {
   wclap_event_header_t header;
   wclap_id param_id;
};
struct wclap_event_transport {
   wclap_event_header_t header;

   uint32_t flags;

   wclap_beattime song_pos_beats;
   wclap_sectime  song_pos_seconds;

   double tempo;
   double tempo_inc;

   wclap_beattime loop_start_beats;
   wclap_beattime loop_end_beats;
   wclap_sectime  loop_start_seconds;
   wclap_sectime  loop_end_seconds;

   wclap_beattime bar_start;
   int32_t       bar_number;

   uint16_t tsig_num;
   uint16_t tsig_denom;
};
struct wclap_event_midi {
   wclap_event_header_t header;

   uint16_t port_index;
   uint8_t  data[3];
};
struct wclap_event_midi_sysex {
   wclap_event_header_t header;

   uint16_t       port_index;
   Pointer<const uint8_t> buffer;
   uint32_t       size;
};
struct wclap_event_midi2 {
   wclap_event_header_t header;

   uint16_t port_index;
   uint32_t data[4];
};
struct wclap_input_events {
   Pointer<void> ctx;
   Function<uint32_t,Pointer<const struct wclap_input_events> list> size;
   Function<Pointer<const wclap_event_header_t> ,Pointer<const struct wclap_input_events> list, uint32_t index> get;
};
struct wclap_output_events {
   Pointer<void> ctx;
   Function<bool,Pointer<const struct wclap_output_events> list,
                            Pointer<const wclap_event_header_t>       event> try_push;
};
struct wclap_audio_buffer {
   Pointer<Pointer<float>>  data32;
   Pointer<Pointer<double>> data64;
   uint32_t channel_count;
   uint32_t latency;
   uint64_t constant_mask;
};
typedef int32_t wclap_process_status;
struct wclap_process {
   int64_t steady_time;
   uint32_t frames_count;
   Pointer<const wclap_event_transport_t> transport;
   Pointer<const wclap_audio_buffer_t> audio_inputs;
   Pointer<wclap_audio_buffer_t>       audio_outputs;
   uint32_t                   audio_inputs_count;
   uint32_t                   audio_outputs_count;
   Pointer<const wclap_input_events_t>  in_events;
   Pointer<const wclap_output_events_t> out_events;
};
struct wclap_plugin_descriptor {
   wclap_version_t wclap_version;
   Pointer<const char> id;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> manual_url;
   Pointer<const char> support_url;
   Pointer<const char> version;
   Pointer<const char> description;
   Pointer<const char> Pointer<const> features;
};
struct wclap_plugin {
   Pointer<const wclap_plugin_descriptor_t> desc;

   Pointer<void> plugin_data;
   Function<bool,Pointer<const struct wclap_plugin> plugin> init;
   Function<void,Pointer<const struct wclap_plugin> plugin> destroy;
   Function<bool,Pointer<const struct wclap_plugin> plugin,
                            double                    sample_rate,
                            uint32_t                  min_frames_count,
                            uint32_t                  max_frames_count> activate;
   Function<void,Pointer<const struct wclap_plugin> plugin> deactivate;
   Function<bool,Pointer<const struct wclap_plugin> plugin> start_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> stop_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> reset;
   Function<wclap_process_status,Pointer<const struct wclap_plugin> plugin,
                                          Pointer<const wclap_process_t>     process> process;
   Function<Pointer<const void> ,Pointer<const struct wclap_plugin> plugin, Pointer<const char> id> get_extension;
   Function<void,Pointer<const struct wclap_plugin> plugin> on_main_thread;
};
typedef uint32_t wclap_context_menu_item_kind_t;
struct wclap_context_menu_target {
   uint32_t kind;
   wclap_id  id;
};
struct wclap_context_menu_entry {
   Pointer<const char> label;
   bool        is_enabled;
   wclap_id     action_id;
};
struct wclap_context_menu_check_entry {
   Pointer<const char> label;
   bool        is_enabled;
   bool        is_checked;
   wclap_id     action_id;
};
struct wclap_context_menu_item_title {
   Pointer<const char> title;
   bool        is_enabled;
};
struct wclap_context_menu_submenu {
   Pointer<const char> label;
   bool        is_enabled;
};
struct wclap_context_menu_builder {
   Pointer<void> ctx;
   Function<bool,Pointer<const struct wclap_context_menu_builder> builder,
                            wclap_context_menu_item_kind_t           item_kind,
                            Pointer<const void>                             item_data> add_item;
   Function<bool,Pointer<const struct wclap_context_menu_builder> builder,
                            wclap_context_menu_item_kind_t           item_kind> supports;
};
struct wclap_plugin_context_menu {
   Function<bool,Pointer<const wclap_plugin_t>               plugin,
                            Pointer<const wclap_context_menu_target_t>  target,
                            Pointer<const wclap_context_menu_builder_t> builder> populate;
   Function<bool,Pointer<const wclap_plugin_t>              plugin,
                           Pointer<const wclap_context_menu_target_t> target,
                           wclap_id                           action_id> perform;
};
struct wclap_host_context_menu {
   Function<bool,Pointer<const wclap_host_t>                 host,
                            Pointer<const wclap_context_menu_target_t>  target,
                            Pointer<const wclap_context_menu_builder_t> builder> populate;
   Function<bool,Pointer<const wclap_host_t>                host,
                           Pointer<const wclap_context_menu_target_t> target,
                           wclap_id                           action_id> perform;
   Function<bool,Pointer<const wclap_host_t> host> can_popup;
   Function<bool,Pointer<const wclap_host_t>                host,
                         Pointer<const wclap_context_menu_target_t> target,
                         int32_t                           screen_index,
                         int32_t                           x,
                         int32_t                           y> popup;
};
struct wclap_version {
   uint32_t major;
   uint32_t minor;
   uint32_t revision;
};
struct wclap_host {
   wclap_version_t wclap_version;

   Pointer<void> host_data;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> version;
   Function<Pointer<const void> ,Pointer<const struct wclap_host> host, Pointer<const char> extension_id> get_extension;
   Function<void,Pointer<const struct wclap_host> host> request_restart;
   Function<void,Pointer<const struct wclap_host> host> request_process;
   Function<void,Pointer<const struct wclap_host> host> request_callback;
};
typedef int64_t wclap_beattime;
typedef int64_t wclap_sectime;
typedef uint32_t wclap_id;
typedef int32_t wclap_note_expression;
struct wclap_event_header {
   uint32_t size;
   uint32_t time;
   uint16_t space_id;
   uint16_t type;
   uint32_t flags;
};
struct wclap_event_note {
   wclap_event_header_t header;

   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;
   double  velocity;
};
struct wclap_event_note_expression {
   wclap_event_header_t header;

   wclap_note_expression expression_id;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_value {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_mod {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double amount;
};
struct wclap_event_param_gesture {
   wclap_event_header_t header;
   wclap_id param_id;
};
struct wclap_event_transport {
   wclap_event_header_t header;

   uint32_t flags;

   wclap_beattime song_pos_beats;
   wclap_sectime  song_pos_seconds;

   double tempo;
   double tempo_inc;

   wclap_beattime loop_start_beats;
   wclap_beattime loop_end_beats;
   wclap_sectime  loop_start_seconds;
   wclap_sectime  loop_end_seconds;

   wclap_beattime bar_start;
   int32_t       bar_number;

   uint16_t tsig_num;
   uint16_t tsig_denom;
};
struct wclap_event_midi {
   wclap_event_header_t header;

   uint16_t port_index;
   uint8_t  data[3];
};
struct wclap_event_midi_sysex {
   wclap_event_header_t header;

   uint16_t       port_index;
   Pointer<const uint8_t> buffer;
   uint32_t       size;
};
struct wclap_event_midi2 {
   wclap_event_header_t header;

   uint16_t port_index;
   uint32_t data[4];
};
struct wclap_input_events {
   Pointer<void> ctx;
   Function<uint32_t,Pointer<const struct wclap_input_events> list> size;
   Function<Pointer<const wclap_event_header_t> ,Pointer<const struct wclap_input_events> list, uint32_t index> get;
};
struct wclap_output_events {
   Pointer<void> ctx;
   Function<bool,Pointer<const struct wclap_output_events> list,
                            Pointer<const wclap_event_header_t>       event> try_push;
};
struct wclap_audio_buffer {
   Pointer<Pointer<float>>  data32;
   Pointer<Pointer<double>> data64;
   uint32_t channel_count;
   uint32_t latency;
   uint64_t constant_mask;
};
typedef int32_t wclap_process_status;
struct wclap_process {
   int64_t steady_time;
   uint32_t frames_count;
   Pointer<const wclap_event_transport_t> transport;
   Pointer<const wclap_audio_buffer_t> audio_inputs;
   Pointer<wclap_audio_buffer_t>       audio_outputs;
   uint32_t                   audio_inputs_count;
   uint32_t                   audio_outputs_count;
   Pointer<const wclap_input_events_t>  in_events;
   Pointer<const wclap_output_events_t> out_events;
};
struct wclap_plugin_descriptor {
   wclap_version_t wclap_version;
   Pointer<const char> id;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> manual_url;
   Pointer<const char> support_url;
   Pointer<const char> version;
   Pointer<const char> description;
   Pointer<const char> Pointer<const> features;
};
struct wclap_plugin {
   Pointer<const wclap_plugin_descriptor_t> desc;

   Pointer<void> plugin_data;
   Function<bool,Pointer<const struct wclap_plugin> plugin> init;
   Function<void,Pointer<const struct wclap_plugin> plugin> destroy;
   Function<bool,Pointer<const struct wclap_plugin> plugin,
                            double                    sample_rate,
                            uint32_t                  min_frames_count,
                            uint32_t                  max_frames_count> activate;
   Function<void,Pointer<const struct wclap_plugin> plugin> deactivate;
   Function<bool,Pointer<const struct wclap_plugin> plugin> start_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> stop_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> reset;
   Function<wclap_process_status,Pointer<const struct wclap_plugin> plugin,
                                          Pointer<const wclap_process_t>     process> process;
   Function<Pointer<const void> ,Pointer<const struct wclap_plugin> plugin, Pointer<const char> id> get_extension;
   Function<void,Pointer<const struct wclap_plugin> plugin> on_main_thread;
};
struct wclap_host_event_registry {
   Function<bool,Pointer<const wclap_host_t> host, Pointer<const char> space_name, Pointer<uint16_t> space_id> query;
};
struct wclap_version {
   uint32_t major;
   uint32_t minor;
   uint32_t revision;
};
struct wclap_host {
   wclap_version_t wclap_version;

   Pointer<void> host_data;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> version;
   Function<Pointer<const void> ,Pointer<const struct wclap_host> host, Pointer<const char> extension_id> get_extension;
   Function<void,Pointer<const struct wclap_host> host> request_restart;
   Function<void,Pointer<const struct wclap_host> host> request_process;
   Function<void,Pointer<const struct wclap_host> host> request_callback;
};
typedef int64_t wclap_beattime;
typedef int64_t wclap_sectime;
typedef uint32_t wclap_id;
typedef int32_t wclap_note_expression;
struct wclap_event_header {
   uint32_t size;
   uint32_t time;
   uint16_t space_id;
   uint16_t type;
   uint32_t flags;
};
struct wclap_event_note {
   wclap_event_header_t header;

   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;
   double  velocity;
};
struct wclap_event_note_expression {
   wclap_event_header_t header;

   wclap_note_expression expression_id;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_value {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_mod {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double amount;
};
struct wclap_event_param_gesture {
   wclap_event_header_t header;
   wclap_id param_id;
};
struct wclap_event_transport {
   wclap_event_header_t header;

   uint32_t flags;

   wclap_beattime song_pos_beats;
   wclap_sectime  song_pos_seconds;

   double tempo;
   double tempo_inc;

   wclap_beattime loop_start_beats;
   wclap_beattime loop_end_beats;
   wclap_sectime  loop_start_seconds;
   wclap_sectime  loop_end_seconds;

   wclap_beattime bar_start;
   int32_t       bar_number;

   uint16_t tsig_num;
   uint16_t tsig_denom;
};
struct wclap_event_midi {
   wclap_event_header_t header;

   uint16_t port_index;
   uint8_t  data[3];
};
struct wclap_event_midi_sysex {
   wclap_event_header_t header;

   uint16_t       port_index;
   Pointer<const uint8_t> buffer;
   uint32_t       size;
};
struct wclap_event_midi2 {
   wclap_event_header_t header;

   uint16_t port_index;
   uint32_t data[4];
};
struct wclap_input_events {
   Pointer<void> ctx;
   Function<uint32_t,Pointer<const struct wclap_input_events> list> size;
   Function<Pointer<const wclap_event_header_t> ,Pointer<const struct wclap_input_events> list, uint32_t index> get;
};
struct wclap_output_events {
   Pointer<void> ctx;
   Function<bool,Pointer<const struct wclap_output_events> list,
                            Pointer<const wclap_event_header_t>       event> try_push;
};
struct wclap_audio_buffer {
   Pointer<Pointer<float>>  data32;
   Pointer<Pointer<double>> data64;
   uint32_t channel_count;
   uint32_t latency;
   uint64_t constant_mask;
};
typedef int32_t wclap_process_status;
struct wclap_process {
   int64_t steady_time;
   uint32_t frames_count;
   Pointer<const wclap_event_transport_t> transport;
   Pointer<const wclap_audio_buffer_t> audio_inputs;
   Pointer<wclap_audio_buffer_t>       audio_outputs;
   uint32_t                   audio_inputs_count;
   uint32_t                   audio_outputs_count;
   Pointer<const wclap_input_events_t>  in_events;
   Pointer<const wclap_output_events_t> out_events;
};
struct wclap_plugin_descriptor {
   wclap_version_t wclap_version;
   Pointer<const char> id;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> manual_url;
   Pointer<const char> support_url;
   Pointer<const char> version;
   Pointer<const char> description;
   Pointer<const char> Pointer<const> features;
};
struct wclap_plugin {
   Pointer<const wclap_plugin_descriptor_t> desc;

   Pointer<void> plugin_data;
   Function<bool,Pointer<const struct wclap_plugin> plugin> init;
   Function<void,Pointer<const struct wclap_plugin> plugin> destroy;
   Function<bool,Pointer<const struct wclap_plugin> plugin,
                            double                    sample_rate,
                            uint32_t                  min_frames_count,
                            uint32_t                  max_frames_count> activate;
   Function<void,Pointer<const struct wclap_plugin> plugin> deactivate;
   Function<bool,Pointer<const struct wclap_plugin> plugin> start_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> stop_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> reset;
   Function<wclap_process_status,Pointer<const struct wclap_plugin> plugin,
                                          Pointer<const wclap_process_t>     process> process;
   Function<Pointer<const void> ,Pointer<const struct wclap_plugin> plugin, Pointer<const char> id> get_extension;
   Function<void,Pointer<const struct wclap_plugin> plugin> on_main_thread;
};
typedef unsigned long wclap_xwnd;
struct wclap_window {
   Pointer<const char> api;
   union {
      wclap_nsview cocoa;
      wclap_xwnd   x11;
      wclap_hwnd   win32;
      Pointer<void>       ptr;
   };
};
struct wclap_gui_resize_hints {
   bool can_resize_horizontally;
   bool can_resize_vertically;
   bool     preserve_aspect_ratio;
   uint32_t aspect_ratio_width;
   uint32_t aspect_ratio_height;
};
struct wclap_plugin_gui {
   Function<bool,Pointer<const wclap_plugin_t> plugin, Pointer<const char> api, bool is_floating> is_api_supported;
   Function<bool,Pointer<const wclap_plugin_t> plugin,
                                     Pointer<Pointer<const char>>         api,
                                     Pointer<bool>                is_floating> get_preferred_api;
   Function<bool,Pointer<const wclap_plugin_t> plugin, Pointer<const char> api, bool is_floating> create;
   Function<void,Pointer<const wclap_plugin_t> plugin> destroy;
   Function<bool,Pointer<const wclap_plugin_t> plugin, double scale> set_scale;
   Function<bool,Pointer<const wclap_plugin_t> plugin, Pointer<uint32_t> width, Pointer<uint32_t> height> get_size;
   Function<bool,Pointer<const wclap_plugin_t> plugin> can_resize;
   Function<bool,Pointer<const wclap_plugin_t> plugin, Pointer<wclap_gui_resize_hints_t> hints> get_resize_hints;
   Function<bool,Pointer<const wclap_plugin_t> plugin, Pointer<uint32_t> width, Pointer<uint32_t> height> adjust_size;
   Function<bool,Pointer<const wclap_plugin_t> plugin, uint32_t width, uint32_t height> set_size;
   Function<bool,Pointer<const wclap_plugin_t> plugin, Pointer<const wclap_window_t> window> set_parent;
   Function<bool,Pointer<const wclap_plugin_t> plugin, Pointer<const wclap_window_t> window> set_transient;
   Function<void,Pointer<const wclap_plugin_t> plugin, Pointer<const char> title> suggest_title;
   Function<bool,Pointer<const wclap_plugin_t> plugin> show;
   Function<bool,Pointer<const wclap_plugin_t> plugin> hide;
};
struct wclap_host_gui {
   Function<void,Pointer<const wclap_host_t> host> resize_hints_changed;
   Function<bool,Pointer<const wclap_host_t> host, uint32_t width, uint32_t height> request_resize;
   Function<bool,Pointer<const wclap_host_t> host> request_show;
   Function<bool,Pointer<const wclap_host_t> host> request_hide;
   Function<void,Pointer<const wclap_host_t> host, bool was_destroyed> closed;
};
struct wclap_version {
   uint32_t major;
   uint32_t minor;
   uint32_t revision;
};
struct wclap_host {
   wclap_version_t wclap_version;

   Pointer<void> host_data;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> version;
   Function<Pointer<const void> ,Pointer<const struct wclap_host> host, Pointer<const char> extension_id> get_extension;
   Function<void,Pointer<const struct wclap_host> host> request_restart;
   Function<void,Pointer<const struct wclap_host> host> request_process;
   Function<void,Pointer<const struct wclap_host> host> request_callback;
};
typedef int64_t wclap_beattime;
typedef int64_t wclap_sectime;
typedef uint32_t wclap_id;
typedef int32_t wclap_note_expression;
struct wclap_event_header {
   uint32_t size;
   uint32_t time;
   uint16_t space_id;
   uint16_t type;
   uint32_t flags;
};
struct wclap_event_note {
   wclap_event_header_t header;

   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;
   double  velocity;
};
struct wclap_event_note_expression {
   wclap_event_header_t header;

   wclap_note_expression expression_id;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_value {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_mod {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double amount;
};
struct wclap_event_param_gesture {
   wclap_event_header_t header;
   wclap_id param_id;
};
struct wclap_event_transport {
   wclap_event_header_t header;

   uint32_t flags;

   wclap_beattime song_pos_beats;
   wclap_sectime  song_pos_seconds;

   double tempo;
   double tempo_inc;

   wclap_beattime loop_start_beats;
   wclap_beattime loop_end_beats;
   wclap_sectime  loop_start_seconds;
   wclap_sectime  loop_end_seconds;

   wclap_beattime bar_start;
   int32_t       bar_number;

   uint16_t tsig_num;
   uint16_t tsig_denom;
};
struct wclap_event_midi {
   wclap_event_header_t header;

   uint16_t port_index;
   uint8_t  data[3];
};
struct wclap_event_midi_sysex {
   wclap_event_header_t header;

   uint16_t       port_index;
   Pointer<const uint8_t> buffer;
   uint32_t       size;
};
struct wclap_event_midi2 {
   wclap_event_header_t header;

   uint16_t port_index;
   uint32_t data[4];
};
struct wclap_input_events {
   Pointer<void> ctx;
   Function<uint32_t,Pointer<const struct wclap_input_events> list> size;
   Function<Pointer<const wclap_event_header_t> ,Pointer<const struct wclap_input_events> list, uint32_t index> get;
};
struct wclap_output_events {
   Pointer<void> ctx;
   Function<bool,Pointer<const struct wclap_output_events> list,
                            Pointer<const wclap_event_header_t>       event> try_push;
};
struct wclap_audio_buffer {
   Pointer<Pointer<float>>  data32;
   Pointer<Pointer<double>> data64;
   uint32_t channel_count;
   uint32_t latency;
   uint64_t constant_mask;
};
typedef int32_t wclap_process_status;
struct wclap_process {
   int64_t steady_time;
   uint32_t frames_count;
   Pointer<const wclap_event_transport_t> transport;
   Pointer<const wclap_audio_buffer_t> audio_inputs;
   Pointer<wclap_audio_buffer_t>       audio_outputs;
   uint32_t                   audio_inputs_count;
   uint32_t                   audio_outputs_count;
   Pointer<const wclap_input_events_t>  in_events;
   Pointer<const wclap_output_events_t> out_events;
};
struct wclap_plugin_descriptor {
   wclap_version_t wclap_version;
   Pointer<const char> id;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> manual_url;
   Pointer<const char> support_url;
   Pointer<const char> version;
   Pointer<const char> description;
   Pointer<const char> Pointer<const> features;
};
struct wclap_plugin {
   Pointer<const wclap_plugin_descriptor_t> desc;

   Pointer<void> plugin_data;
   Function<bool,Pointer<const struct wclap_plugin> plugin> init;
   Function<void,Pointer<const struct wclap_plugin> plugin> destroy;
   Function<bool,Pointer<const struct wclap_plugin> plugin,
                            double                    sample_rate,
                            uint32_t                  min_frames_count,
                            uint32_t                  max_frames_count> activate;
   Function<void,Pointer<const struct wclap_plugin> plugin> deactivate;
   Function<bool,Pointer<const struct wclap_plugin> plugin> start_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> stop_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> reset;
   Function<wclap_process_status,Pointer<const struct wclap_plugin> plugin,
                                          Pointer<const wclap_process_t>     process> process;
   Function<Pointer<const void> ,Pointer<const struct wclap_plugin> plugin, Pointer<const char> id> get_extension;
   Function<void,Pointer<const struct wclap_plugin> plugin> on_main_thread;
};
struct wclap_plugin_latency {
   Function<uint32_t,Pointer<const wclap_plugin_t> plugin> get;
};
struct wclap_host_latency {
   Function<void,Pointer<const wclap_host_t> host> changed;
};
struct wclap_version {
   uint32_t major;
   uint32_t minor;
   uint32_t revision;
};
struct wclap_host {
   wclap_version_t wclap_version;

   Pointer<void> host_data;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> version;
   Function<Pointer<const void> ,Pointer<const struct wclap_host> host, Pointer<const char> extension_id> get_extension;
   Function<void,Pointer<const struct wclap_host> host> request_restart;
   Function<void,Pointer<const struct wclap_host> host> request_process;
   Function<void,Pointer<const struct wclap_host> host> request_callback;
};
typedef int64_t wclap_beattime;
typedef int64_t wclap_sectime;
typedef uint32_t wclap_id;
typedef int32_t wclap_note_expression;
struct wclap_event_header {
   uint32_t size;
   uint32_t time;
   uint16_t space_id;
   uint16_t type;
   uint32_t flags;
};
struct wclap_event_note {
   wclap_event_header_t header;

   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;
   double  velocity;
};
struct wclap_event_note_expression {
   wclap_event_header_t header;

   wclap_note_expression expression_id;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_value {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_mod {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double amount;
};
struct wclap_event_param_gesture {
   wclap_event_header_t header;
   wclap_id param_id;
};
struct wclap_event_transport {
   wclap_event_header_t header;

   uint32_t flags;

   wclap_beattime song_pos_beats;
   wclap_sectime  song_pos_seconds;

   double tempo;
   double tempo_inc;

   wclap_beattime loop_start_beats;
   wclap_beattime loop_end_beats;
   wclap_sectime  loop_start_seconds;
   wclap_sectime  loop_end_seconds;

   wclap_beattime bar_start;
   int32_t       bar_number;

   uint16_t tsig_num;
   uint16_t tsig_denom;
};
struct wclap_event_midi {
   wclap_event_header_t header;

   uint16_t port_index;
   uint8_t  data[3];
};
struct wclap_event_midi_sysex {
   wclap_event_header_t header;

   uint16_t       port_index;
   Pointer<const uint8_t> buffer;
   uint32_t       size;
};
struct wclap_event_midi2 {
   wclap_event_header_t header;

   uint16_t port_index;
   uint32_t data[4];
};
struct wclap_input_events {
   Pointer<void> ctx;
   Function<uint32_t,Pointer<const struct wclap_input_events> list> size;
   Function<Pointer<const wclap_event_header_t> ,Pointer<const struct wclap_input_events> list, uint32_t index> get;
};
struct wclap_output_events {
   Pointer<void> ctx;
   Function<bool,Pointer<const struct wclap_output_events> list,
                            Pointer<const wclap_event_header_t>       event> try_push;
};
struct wclap_audio_buffer {
   Pointer<Pointer<float>>  data32;
   Pointer<Pointer<double>> data64;
   uint32_t channel_count;
   uint32_t latency;
   uint64_t constant_mask;
};
typedef int32_t wclap_process_status;
struct wclap_process {
   int64_t steady_time;
   uint32_t frames_count;
   Pointer<const wclap_event_transport_t> transport;
   Pointer<const wclap_audio_buffer_t> audio_inputs;
   Pointer<wclap_audio_buffer_t>       audio_outputs;
   uint32_t                   audio_inputs_count;
   uint32_t                   audio_outputs_count;
   Pointer<const wclap_input_events_t>  in_events;
   Pointer<const wclap_output_events_t> out_events;
};
struct wclap_plugin_descriptor {
   wclap_version_t wclap_version;
   Pointer<const char> id;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> manual_url;
   Pointer<const char> support_url;
   Pointer<const char> version;
   Pointer<const char> description;
   Pointer<const char> Pointer<const> features;
};
struct wclap_plugin {
   Pointer<const wclap_plugin_descriptor_t> desc;

   Pointer<void> plugin_data;
   Function<bool,Pointer<const struct wclap_plugin> plugin> init;
   Function<void,Pointer<const struct wclap_plugin> plugin> destroy;
   Function<bool,Pointer<const struct wclap_plugin> plugin,
                            double                    sample_rate,
                            uint32_t                  min_frames_count,
                            uint32_t                  max_frames_count> activate;
   Function<void,Pointer<const struct wclap_plugin> plugin> deactivate;
   Function<bool,Pointer<const struct wclap_plugin> plugin> start_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> stop_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> reset;
   Function<wclap_process_status,Pointer<const struct wclap_plugin> plugin,
                                          Pointer<const wclap_process_t>     process> process;
   Function<Pointer<const void> ,Pointer<const struct wclap_plugin> plugin, Pointer<const char> id> get_extension;
   Function<void,Pointer<const struct wclap_plugin> plugin> on_main_thread;
};
typedef int32_t wclap_log_severity;
struct wclap_host_log {
   Function<void,Pointer<const wclap_host_t> host, wclap_log_severity severity, Pointer<const char> msg> log;
};
struct wclap_version {
   uint32_t major;
   uint32_t minor;
   uint32_t revision;
};
struct wclap_host {
   wclap_version_t wclap_version;

   Pointer<void> host_data;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> version;
   Function<Pointer<const void> ,Pointer<const struct wclap_host> host, Pointer<const char> extension_id> get_extension;
   Function<void,Pointer<const struct wclap_host> host> request_restart;
   Function<void,Pointer<const struct wclap_host> host> request_process;
   Function<void,Pointer<const struct wclap_host> host> request_callback;
};
typedef int64_t wclap_beattime;
typedef int64_t wclap_sectime;
typedef uint32_t wclap_id;
typedef int32_t wclap_note_expression;
struct wclap_event_header {
   uint32_t size;
   uint32_t time;
   uint16_t space_id;
   uint16_t type;
   uint32_t flags;
};
struct wclap_event_note {
   wclap_event_header_t header;

   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;
   double  velocity;
};
struct wclap_event_note_expression {
   wclap_event_header_t header;

   wclap_note_expression expression_id;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_value {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_mod {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double amount;
};
struct wclap_event_param_gesture {
   wclap_event_header_t header;
   wclap_id param_id;
};
struct wclap_event_transport {
   wclap_event_header_t header;

   uint32_t flags;

   wclap_beattime song_pos_beats;
   wclap_sectime  song_pos_seconds;

   double tempo;
   double tempo_inc;

   wclap_beattime loop_start_beats;
   wclap_beattime loop_end_beats;
   wclap_sectime  loop_start_seconds;
   wclap_sectime  loop_end_seconds;

   wclap_beattime bar_start;
   int32_t       bar_number;

   uint16_t tsig_num;
   uint16_t tsig_denom;
};
struct wclap_event_midi {
   wclap_event_header_t header;

   uint16_t port_index;
   uint8_t  data[3];
};
struct wclap_event_midi_sysex {
   wclap_event_header_t header;

   uint16_t       port_index;
   Pointer<const uint8_t> buffer;
   uint32_t       size;
};
struct wclap_event_midi2 {
   wclap_event_header_t header;

   uint16_t port_index;
   uint32_t data[4];
};
struct wclap_input_events {
   Pointer<void> ctx;
   Function<uint32_t,Pointer<const struct wclap_input_events> list> size;
   Function<Pointer<const wclap_event_header_t> ,Pointer<const struct wclap_input_events> list, uint32_t index> get;
};
struct wclap_output_events {
   Pointer<void> ctx;
   Function<bool,Pointer<const struct wclap_output_events> list,
                            Pointer<const wclap_event_header_t>       event> try_push;
};
struct wclap_audio_buffer {
   Pointer<Pointer<float>>  data32;
   Pointer<Pointer<double>> data64;
   uint32_t channel_count;
   uint32_t latency;
   uint64_t constant_mask;
};
typedef int32_t wclap_process_status;
struct wclap_process {
   int64_t steady_time;
   uint32_t frames_count;
   Pointer<const wclap_event_transport_t> transport;
   Pointer<const wclap_audio_buffer_t> audio_inputs;
   Pointer<wclap_audio_buffer_t>       audio_outputs;
   uint32_t                   audio_inputs_count;
   uint32_t                   audio_outputs_count;
   Pointer<const wclap_input_events_t>  in_events;
   Pointer<const wclap_output_events_t> out_events;
};
struct wclap_plugin_descriptor {
   wclap_version_t wclap_version;
   Pointer<const char> id;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> manual_url;
   Pointer<const char> support_url;
   Pointer<const char> version;
   Pointer<const char> description;
   Pointer<const char> Pointer<const> features;
};
struct wclap_plugin {
   Pointer<const wclap_plugin_descriptor_t> desc;

   Pointer<void> plugin_data;
   Function<bool,Pointer<const struct wclap_plugin> plugin> init;
   Function<void,Pointer<const struct wclap_plugin> plugin> destroy;
   Function<bool,Pointer<const struct wclap_plugin> plugin,
                            double                    sample_rate,
                            uint32_t                  min_frames_count,
                            uint32_t                  max_frames_count> activate;
   Function<void,Pointer<const struct wclap_plugin> plugin> deactivate;
   Function<bool,Pointer<const struct wclap_plugin> plugin> start_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> stop_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> reset;
   Function<wclap_process_status,Pointer<const struct wclap_plugin> plugin,
                                          Pointer<const wclap_process_t>     process> process;
   Function<Pointer<const void> ,Pointer<const struct wclap_plugin> plugin, Pointer<const char> id> get_extension;
   Function<void,Pointer<const struct wclap_plugin> plugin> on_main_thread;
};
struct wclap_note_name {
   char    name[CLAP_NAME_SIZE];
   int16_t port;
   int16_t key;
   int16_t channel;
};
struct wclap_plugin_note_name {
   Function<uint32_t,Pointer<const wclap_plugin_t> plugin> count;
   Function<bool,Pointer<const wclap_plugin_t> plugin, uint32_t index, Pointer<wclap_note_name_t> note_name> get;
};
struct wclap_host_note_name {
   Function<void,Pointer<const wclap_host_t> host> changed;
};
struct wclap_version {
   uint32_t major;
   uint32_t minor;
   uint32_t revision;
};
struct wclap_host {
   wclap_version_t wclap_version;

   Pointer<void> host_data;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> version;
   Function<Pointer<const void> ,Pointer<const struct wclap_host> host, Pointer<const char> extension_id> get_extension;
   Function<void,Pointer<const struct wclap_host> host> request_restart;
   Function<void,Pointer<const struct wclap_host> host> request_process;
   Function<void,Pointer<const struct wclap_host> host> request_callback;
};
typedef int64_t wclap_beattime;
typedef int64_t wclap_sectime;
typedef uint32_t wclap_id;
typedef int32_t wclap_note_expression;
struct wclap_event_header {
   uint32_t size;
   uint32_t time;
   uint16_t space_id;
   uint16_t type;
   uint32_t flags;
};
struct wclap_event_note {
   wclap_event_header_t header;

   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;
   double  velocity;
};
struct wclap_event_note_expression {
   wclap_event_header_t header;

   wclap_note_expression expression_id;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_value {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_mod {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double amount;
};
struct wclap_event_param_gesture {
   wclap_event_header_t header;
   wclap_id param_id;
};
struct wclap_event_transport {
   wclap_event_header_t header;

   uint32_t flags;

   wclap_beattime song_pos_beats;
   wclap_sectime  song_pos_seconds;

   double tempo;
   double tempo_inc;

   wclap_beattime loop_start_beats;
   wclap_beattime loop_end_beats;
   wclap_sectime  loop_start_seconds;
   wclap_sectime  loop_end_seconds;

   wclap_beattime bar_start;
   int32_t       bar_number;

   uint16_t tsig_num;
   uint16_t tsig_denom;
};
struct wclap_event_midi {
   wclap_event_header_t header;

   uint16_t port_index;
   uint8_t  data[3];
};
struct wclap_event_midi_sysex {
   wclap_event_header_t header;

   uint16_t       port_index;
   Pointer<const uint8_t> buffer;
   uint32_t       size;
};
struct wclap_event_midi2 {
   wclap_event_header_t header;

   uint16_t port_index;
   uint32_t data[4];
};
struct wclap_input_events {
   Pointer<void> ctx;
   Function<uint32_t,Pointer<const struct wclap_input_events> list> size;
   Function<Pointer<const wclap_event_header_t> ,Pointer<const struct wclap_input_events> list, uint32_t index> get;
};
struct wclap_output_events {
   Pointer<void> ctx;
   Function<bool,Pointer<const struct wclap_output_events> list,
                            Pointer<const wclap_event_header_t>       event> try_push;
};
struct wclap_audio_buffer {
   Pointer<Pointer<float>>  data32;
   Pointer<Pointer<double>> data64;
   uint32_t channel_count;
   uint32_t latency;
   uint64_t constant_mask;
};
typedef int32_t wclap_process_status;
struct wclap_process {
   int64_t steady_time;
   uint32_t frames_count;
   Pointer<const wclap_event_transport_t> transport;
   Pointer<const wclap_audio_buffer_t> audio_inputs;
   Pointer<wclap_audio_buffer_t>       audio_outputs;
   uint32_t                   audio_inputs_count;
   uint32_t                   audio_outputs_count;
   Pointer<const wclap_input_events_t>  in_events;
   Pointer<const wclap_output_events_t> out_events;
};
struct wclap_plugin_descriptor {
   wclap_version_t wclap_version;
   Pointer<const char> id;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> manual_url;
   Pointer<const char> support_url;
   Pointer<const char> version;
   Pointer<const char> description;
   Pointer<const char> Pointer<const> features;
};
struct wclap_plugin {
   Pointer<const wclap_plugin_descriptor_t> desc;

   Pointer<void> plugin_data;
   Function<bool,Pointer<const struct wclap_plugin> plugin> init;
   Function<void,Pointer<const struct wclap_plugin> plugin> destroy;
   Function<bool,Pointer<const struct wclap_plugin> plugin,
                            double                    sample_rate,
                            uint32_t                  min_frames_count,
                            uint32_t                  max_frames_count> activate;
   Function<void,Pointer<const struct wclap_plugin> plugin> deactivate;
   Function<bool,Pointer<const struct wclap_plugin> plugin> start_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> stop_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> reset;
   Function<wclap_process_status,Pointer<const struct wclap_plugin> plugin,
                                          Pointer<const wclap_process_t>     process> process;
   Function<Pointer<const void> ,Pointer<const struct wclap_plugin> plugin, Pointer<const char> id> get_extension;
   Function<void,Pointer<const struct wclap_plugin> plugin> on_main_thread;
};
struct wclap_note_port_info {
   wclap_id  id;
   uint32_t supported_dialects;
   uint32_t preferred_dialect;
   char     name[CLAP_NAME_SIZE];
};
struct wclap_plugin_note_ports {
   Function<uint32_t,Pointer<const wclap_plugin_t> plugin, bool is_input> count;
   Function<bool,Pointer<const wclap_plugin_t>   plugin,
                       uint32_t               index,
                       bool                   is_input,
                       Pointer<wclap_note_port_info_t> info> get;
};
struct wclap_host_note_ports {
   Function<uint32_t,Pointer<const wclap_host_t> host> supported_dialects;
   Function<void,Pointer<const wclap_host_t> host, uint32_t flags> rescan;
};
struct wclap_version {
   uint32_t major;
   uint32_t minor;
   uint32_t revision;
};
struct wclap_host {
   wclap_version_t wclap_version;

   Pointer<void> host_data;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> version;
   Function<Pointer<const void> ,Pointer<const struct wclap_host> host, Pointer<const char> extension_id> get_extension;
   Function<void,Pointer<const struct wclap_host> host> request_restart;
   Function<void,Pointer<const struct wclap_host> host> request_process;
   Function<void,Pointer<const struct wclap_host> host> request_callback;
};
typedef int64_t wclap_beattime;
typedef int64_t wclap_sectime;
typedef uint32_t wclap_id;
typedef int32_t wclap_note_expression;
struct wclap_event_header {
   uint32_t size;
   uint32_t time;
   uint16_t space_id;
   uint16_t type;
   uint32_t flags;
};
struct wclap_event_note {
   wclap_event_header_t header;

   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;
   double  velocity;
};
struct wclap_event_note_expression {
   wclap_event_header_t header;

   wclap_note_expression expression_id;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_value {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_mod {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double amount;
};
struct wclap_event_param_gesture {
   wclap_event_header_t header;
   wclap_id param_id;
};
struct wclap_event_transport {
   wclap_event_header_t header;

   uint32_t flags;

   wclap_beattime song_pos_beats;
   wclap_sectime  song_pos_seconds;

   double tempo;
   double tempo_inc;

   wclap_beattime loop_start_beats;
   wclap_beattime loop_end_beats;
   wclap_sectime  loop_start_seconds;
   wclap_sectime  loop_end_seconds;

   wclap_beattime bar_start;
   int32_t       bar_number;

   uint16_t tsig_num;
   uint16_t tsig_denom;
};
struct wclap_event_midi {
   wclap_event_header_t header;

   uint16_t port_index;
   uint8_t  data[3];
};
struct wclap_event_midi_sysex {
   wclap_event_header_t header;

   uint16_t       port_index;
   Pointer<const uint8_t> buffer;
   uint32_t       size;
};
struct wclap_event_midi2 {
   wclap_event_header_t header;

   uint16_t port_index;
   uint32_t data[4];
};
struct wclap_input_events {
   Pointer<void> ctx;
   Function<uint32_t,Pointer<const struct wclap_input_events> list> size;
   Function<Pointer<const wclap_event_header_t> ,Pointer<const struct wclap_input_events> list, uint32_t index> get;
};
struct wclap_output_events {
   Pointer<void> ctx;
   Function<bool,Pointer<const struct wclap_output_events> list,
                            Pointer<const wclap_event_header_t>       event> try_push;
};
struct wclap_audio_buffer {
   Pointer<Pointer<float>>  data32;
   Pointer<Pointer<double>> data64;
   uint32_t channel_count;
   uint32_t latency;
   uint64_t constant_mask;
};
typedef int32_t wclap_process_status;
struct wclap_process {
   int64_t steady_time;
   uint32_t frames_count;
   Pointer<const wclap_event_transport_t> transport;
   Pointer<const wclap_audio_buffer_t> audio_inputs;
   Pointer<wclap_audio_buffer_t>       audio_outputs;
   uint32_t                   audio_inputs_count;
   uint32_t                   audio_outputs_count;
   Pointer<const wclap_input_events_t>  in_events;
   Pointer<const wclap_output_events_t> out_events;
};
struct wclap_plugin_descriptor {
   wclap_version_t wclap_version;
   Pointer<const char> id;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> manual_url;
   Pointer<const char> support_url;
   Pointer<const char> version;
   Pointer<const char> description;
   Pointer<const char> Pointer<const> features;
};
struct wclap_plugin {
   Pointer<const wclap_plugin_descriptor_t> desc;

   Pointer<void> plugin_data;
   Function<bool,Pointer<const struct wclap_plugin> plugin> init;
   Function<void,Pointer<const struct wclap_plugin> plugin> destroy;
   Function<bool,Pointer<const struct wclap_plugin> plugin,
                            double                    sample_rate,
                            uint32_t                  min_frames_count,
                            uint32_t                  max_frames_count> activate;
   Function<void,Pointer<const struct wclap_plugin> plugin> deactivate;
   Function<bool,Pointer<const struct wclap_plugin> plugin> start_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> stop_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> reset;
   Function<wclap_process_status,Pointer<const struct wclap_plugin> plugin,
                                          Pointer<const wclap_process_t>     process> process;
   Function<Pointer<const void> ,Pointer<const struct wclap_plugin> plugin, Pointer<const char> id> get_extension;
   Function<void,Pointer<const struct wclap_plugin> plugin> on_main_thread;
};
typedef uint32_t wclap_param_info_flags;
typedef uint32_t wclap_param_rescan_flags;
typedef uint32_t wclap_param_clear_flags;
struct wclap_param_info {
   wclap_id id;

   wclap_param_info_flags flags;
   Pointer<void> cookie;
   char name[CLAP_NAME_SIZE];
   char module[CLAP_PATH_SIZE];

   double min_value;
   double max_value;
   double default_value;
};
struct wclap_plugin_params {
   Function<uint32_t,Pointer<const wclap_plugin_t> plugin> count;
   Function<bool,Pointer<const wclap_plugin_t> plugin,
                            uint32_t             param_index,
                            Pointer<wclap_param_info_t>   param_info> get_info;
   Function<bool,Pointer<const wclap_plugin_t> plugin, wclap_id param_id, Pointer<double> out_value> get_value;
   Function<bool,Pointer<const wclap_plugin_t> plugin,
                                 wclap_id              param_id,
                                 double               value,
                                 Pointer<char>                out_buffer,
                                 uint32_t             out_buffer_capacity> value_to_text;
   Function<bool,Pointer<const wclap_plugin_t> plugin,
                                 wclap_id              param_id,
                                 Pointer<const char>          param_value_text,
                                 Pointer<double>              out_value> text_to_value;
   Function<void,Pointer<const wclap_plugin_t>        plugin,
                         Pointer<const wclap_input_events_t>  in,
                         Pointer<const wclap_output_events_t> out> flush;
};
struct wclap_host_params {
   Function<void,Pointer<const wclap_host_t> host, wclap_param_rescan_flags flags> rescan;
   Function<void,Pointer<const wclap_host_t> host, wclap_id param_id, wclap_param_clear_flags flags> clear;
   Function<void,Pointer<const wclap_host_t> host> request_flush;
};
struct wclap_color {
   uint8_t alpha;
   uint8_t red;
   uint8_t green;
   uint8_t blue;
};
struct wclap_plugin_param_indication {
   Function<void,Pointer<const wclap_plugin_t> plugin,
                               wclap_id              param_id,
                               bool                 has_mapping,
                               Pointer<const wclap_color_t>  color,
                               Pointer<const char>          label,
                               Pointer<const char>          description> set_mapping;
   Function<void,Pointer<const wclap_plugin_t> plugin,
                                  wclap_id              param_id,
                                  uint32_t             automation_state,
                                  Pointer<const wclap_color_t>  color> set_automation;
};
struct wclap_version {
   uint32_t major;
   uint32_t minor;
   uint32_t revision;
};
struct wclap_host {
   wclap_version_t wclap_version;

   Pointer<void> host_data;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> version;
   Function<Pointer<const void> ,Pointer<const struct wclap_host> host, Pointer<const char> extension_id> get_extension;
   Function<void,Pointer<const struct wclap_host> host> request_restart;
   Function<void,Pointer<const struct wclap_host> host> request_process;
   Function<void,Pointer<const struct wclap_host> host> request_callback;
};
typedef int64_t wclap_beattime;
typedef int64_t wclap_sectime;
typedef uint32_t wclap_id;
typedef int32_t wclap_note_expression;
struct wclap_event_header {
   uint32_t size;
   uint32_t time;
   uint16_t space_id;
   uint16_t type;
   uint32_t flags;
};
struct wclap_event_note {
   wclap_event_header_t header;

   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;
   double  velocity;
};
struct wclap_event_note_expression {
   wclap_event_header_t header;

   wclap_note_expression expression_id;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_value {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_mod {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double amount;
};
struct wclap_event_param_gesture {
   wclap_event_header_t header;
   wclap_id param_id;
};
struct wclap_event_transport {
   wclap_event_header_t header;

   uint32_t flags;

   wclap_beattime song_pos_beats;
   wclap_sectime  song_pos_seconds;

   double tempo;
   double tempo_inc;

   wclap_beattime loop_start_beats;
   wclap_beattime loop_end_beats;
   wclap_sectime  loop_start_seconds;
   wclap_sectime  loop_end_seconds;

   wclap_beattime bar_start;
   int32_t       bar_number;

   uint16_t tsig_num;
   uint16_t tsig_denom;
};
struct wclap_event_midi {
   wclap_event_header_t header;

   uint16_t port_index;
   uint8_t  data[3];
};
struct wclap_event_midi_sysex {
   wclap_event_header_t header;

   uint16_t       port_index;
   Pointer<const uint8_t> buffer;
   uint32_t       size;
};
struct wclap_event_midi2 {
   wclap_event_header_t header;

   uint16_t port_index;
   uint32_t data[4];
};
struct wclap_input_events {
   Pointer<void> ctx;
   Function<uint32_t,Pointer<const struct wclap_input_events> list> size;
   Function<Pointer<const wclap_event_header_t> ,Pointer<const struct wclap_input_events> list, uint32_t index> get;
};
struct wclap_output_events {
   Pointer<void> ctx;
   Function<bool,Pointer<const struct wclap_output_events> list,
                            Pointer<const wclap_event_header_t>       event> try_push;
};
struct wclap_audio_buffer {
   Pointer<Pointer<float>>  data32;
   Pointer<Pointer<double>> data64;
   uint32_t channel_count;
   uint32_t latency;
   uint64_t constant_mask;
};
typedef int32_t wclap_process_status;
struct wclap_process {
   int64_t steady_time;
   uint32_t frames_count;
   Pointer<const wclap_event_transport_t> transport;
   Pointer<const wclap_audio_buffer_t> audio_inputs;
   Pointer<wclap_audio_buffer_t>       audio_outputs;
   uint32_t                   audio_inputs_count;
   uint32_t                   audio_outputs_count;
   Pointer<const wclap_input_events_t>  in_events;
   Pointer<const wclap_output_events_t> out_events;
};
struct wclap_plugin_descriptor {
   wclap_version_t wclap_version;
   Pointer<const char> id;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> manual_url;
   Pointer<const char> support_url;
   Pointer<const char> version;
   Pointer<const char> description;
   Pointer<const char> Pointer<const> features;
};
struct wclap_plugin {
   Pointer<const wclap_plugin_descriptor_t> desc;

   Pointer<void> plugin_data;
   Function<bool,Pointer<const struct wclap_plugin> plugin> init;
   Function<void,Pointer<const struct wclap_plugin> plugin> destroy;
   Function<bool,Pointer<const struct wclap_plugin> plugin,
                            double                    sample_rate,
                            uint32_t                  min_frames_count,
                            uint32_t                  max_frames_count> activate;
   Function<void,Pointer<const struct wclap_plugin> plugin> deactivate;
   Function<bool,Pointer<const struct wclap_plugin> plugin> start_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> stop_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> reset;
   Function<wclap_process_status,Pointer<const struct wclap_plugin> plugin,
                                          Pointer<const wclap_process_t>     process> process;
   Function<Pointer<const void> ,Pointer<const struct wclap_plugin> plugin, Pointer<const char> id> get_extension;
   Function<void,Pointer<const struct wclap_plugin> plugin> on_main_thread;
};
typedef uint32_t wclap_param_info_flags;
typedef uint32_t wclap_param_rescan_flags;
typedef uint32_t wclap_param_clear_flags;
struct wclap_param_info {
   wclap_id id;

   wclap_param_info_flags flags;
   Pointer<void> cookie;
   char name[CLAP_NAME_SIZE];
   char module[CLAP_PATH_SIZE];

   double min_value;
   double max_value;
   double default_value;
};
struct wclap_plugin_params {
   Function<uint32_t,Pointer<const wclap_plugin_t> plugin> count;
   Function<bool,Pointer<const wclap_plugin_t> plugin,
                            uint32_t             param_index,
                            Pointer<wclap_param_info_t>   param_info> get_info;
   Function<bool,Pointer<const wclap_plugin_t> plugin, wclap_id param_id, Pointer<double> out_value> get_value;
   Function<bool,Pointer<const wclap_plugin_t> plugin,
                                 wclap_id              param_id,
                                 double               value,
                                 Pointer<char>                out_buffer,
                                 uint32_t             out_buffer_capacity> value_to_text;
   Function<bool,Pointer<const wclap_plugin_t> plugin,
                                 wclap_id              param_id,
                                 Pointer<const char>          param_value_text,
                                 Pointer<double>              out_value> text_to_value;
   Function<void,Pointer<const wclap_plugin_t>        plugin,
                         Pointer<const wclap_input_events_t>  in,
                         Pointer<const wclap_output_events_t> out> flush;
};
struct wclap_host_params {
   Function<void,Pointer<const wclap_host_t> host, wclap_param_rescan_flags flags> rescan;
   Function<void,Pointer<const wclap_host_t> host, wclap_id param_id, wclap_param_clear_flags flags> clear;
   Function<void,Pointer<const wclap_host_t> host> request_flush;
};
struct wclap_version {
   uint32_t major;
   uint32_t minor;
   uint32_t revision;
};
struct wclap_host {
   wclap_version_t wclap_version;

   Pointer<void> host_data;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> version;
   Function<Pointer<const void> ,Pointer<const struct wclap_host> host, Pointer<const char> extension_id> get_extension;
   Function<void,Pointer<const struct wclap_host> host> request_restart;
   Function<void,Pointer<const struct wclap_host> host> request_process;
   Function<void,Pointer<const struct wclap_host> host> request_callback;
};
typedef int64_t wclap_beattime;
typedef int64_t wclap_sectime;
typedef uint32_t wclap_id;
typedef int32_t wclap_note_expression;
struct wclap_event_header {
   uint32_t size;
   uint32_t time;
   uint16_t space_id;
   uint16_t type;
   uint32_t flags;
};
struct wclap_event_note {
   wclap_event_header_t header;

   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;
   double  velocity;
};
struct wclap_event_note_expression {
   wclap_event_header_t header;

   wclap_note_expression expression_id;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_value {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_mod {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double amount;
};
struct wclap_event_param_gesture {
   wclap_event_header_t header;
   wclap_id param_id;
};
struct wclap_event_transport {
   wclap_event_header_t header;

   uint32_t flags;

   wclap_beattime song_pos_beats;
   wclap_sectime  song_pos_seconds;

   double tempo;
   double tempo_inc;

   wclap_beattime loop_start_beats;
   wclap_beattime loop_end_beats;
   wclap_sectime  loop_start_seconds;
   wclap_sectime  loop_end_seconds;

   wclap_beattime bar_start;
   int32_t       bar_number;

   uint16_t tsig_num;
   uint16_t tsig_denom;
};
struct wclap_event_midi {
   wclap_event_header_t header;

   uint16_t port_index;
   uint8_t  data[3];
};
struct wclap_event_midi_sysex {
   wclap_event_header_t header;

   uint16_t       port_index;
   Pointer<const uint8_t> buffer;
   uint32_t       size;
};
struct wclap_event_midi2 {
   wclap_event_header_t header;

   uint16_t port_index;
   uint32_t data[4];
};
struct wclap_input_events {
   Pointer<void> ctx;
   Function<uint32_t,Pointer<const struct wclap_input_events> list> size;
   Function<Pointer<const wclap_event_header_t> ,Pointer<const struct wclap_input_events> list, uint32_t index> get;
};
struct wclap_output_events {
   Pointer<void> ctx;
   Function<bool,Pointer<const struct wclap_output_events> list,
                            Pointer<const wclap_event_header_t>       event> try_push;
};
struct wclap_audio_buffer {
   Pointer<Pointer<float>>  data32;
   Pointer<Pointer<double>> data64;
   uint32_t channel_count;
   uint32_t latency;
   uint64_t constant_mask;
};
typedef int32_t wclap_process_status;
struct wclap_process {
   int64_t steady_time;
   uint32_t frames_count;
   Pointer<const wclap_event_transport_t> transport;
   Pointer<const wclap_audio_buffer_t> audio_inputs;
   Pointer<wclap_audio_buffer_t>       audio_outputs;
   uint32_t                   audio_inputs_count;
   uint32_t                   audio_outputs_count;
   Pointer<const wclap_input_events_t>  in_events;
   Pointer<const wclap_output_events_t> out_events;
};
struct wclap_plugin_descriptor {
   wclap_version_t wclap_version;
   Pointer<const char> id;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> manual_url;
   Pointer<const char> support_url;
   Pointer<const char> version;
   Pointer<const char> description;
   Pointer<const char> Pointer<const> features;
};
struct wclap_plugin {
   Pointer<const wclap_plugin_descriptor_t> desc;

   Pointer<void> plugin_data;
   Function<bool,Pointer<const struct wclap_plugin> plugin> init;
   Function<void,Pointer<const struct wclap_plugin> plugin> destroy;
   Function<bool,Pointer<const struct wclap_plugin> plugin,
                            double                    sample_rate,
                            uint32_t                  min_frames_count,
                            uint32_t                  max_frames_count> activate;
   Function<void,Pointer<const struct wclap_plugin> plugin> deactivate;
   Function<bool,Pointer<const struct wclap_plugin> plugin> start_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> stop_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> reset;
   Function<wclap_process_status,Pointer<const struct wclap_plugin> plugin,
                                          Pointer<const wclap_process_t>     process> process;
   Function<Pointer<const void> ,Pointer<const struct wclap_plugin> plugin, Pointer<const char> id> get_extension;
   Function<void,Pointer<const struct wclap_plugin> plugin> on_main_thread;
};
typedef uint32_t wclap_posix_fd_flags_t;
struct wclap_plugin_posix_fd_support {
   Function<void,Pointer<const wclap_plugin_t> plugin, int fd, wclap_posix_fd_flags_t flags> on_fd;
};
struct wclap_host_posix_fd_support {
   Function<bool,Pointer<const wclap_host_t> host, int fd, wclap_posix_fd_flags_t flags> register_fd;
   Function<bool,Pointer<const wclap_host_t> host, int fd, wclap_posix_fd_flags_t flags> modify_fd;
   Function<bool,Pointer<const wclap_host_t> host, int fd> unregister_fd;
};
struct wclap_version {
   uint32_t major;
   uint32_t minor;
   uint32_t revision;
};
struct wclap_host {
   wclap_version_t wclap_version;

   Pointer<void> host_data;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> version;
   Function<Pointer<const void> ,Pointer<const struct wclap_host> host, Pointer<const char> extension_id> get_extension;
   Function<void,Pointer<const struct wclap_host> host> request_restart;
   Function<void,Pointer<const struct wclap_host> host> request_process;
   Function<void,Pointer<const struct wclap_host> host> request_callback;
};
typedef int64_t wclap_beattime;
typedef int64_t wclap_sectime;
typedef uint32_t wclap_id;
typedef int32_t wclap_note_expression;
struct wclap_event_header {
   uint32_t size;
   uint32_t time;
   uint16_t space_id;
   uint16_t type;
   uint32_t flags;
};
struct wclap_event_note {
   wclap_event_header_t header;

   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;
   double  velocity;
};
struct wclap_event_note_expression {
   wclap_event_header_t header;

   wclap_note_expression expression_id;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_value {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_mod {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double amount;
};
struct wclap_event_param_gesture {
   wclap_event_header_t header;
   wclap_id param_id;
};
struct wclap_event_transport {
   wclap_event_header_t header;

   uint32_t flags;

   wclap_beattime song_pos_beats;
   wclap_sectime  song_pos_seconds;

   double tempo;
   double tempo_inc;

   wclap_beattime loop_start_beats;
   wclap_beattime loop_end_beats;
   wclap_sectime  loop_start_seconds;
   wclap_sectime  loop_end_seconds;

   wclap_beattime bar_start;
   int32_t       bar_number;

   uint16_t tsig_num;
   uint16_t tsig_denom;
};
struct wclap_event_midi {
   wclap_event_header_t header;

   uint16_t port_index;
   uint8_t  data[3];
};
struct wclap_event_midi_sysex {
   wclap_event_header_t header;

   uint16_t       port_index;
   Pointer<const uint8_t> buffer;
   uint32_t       size;
};
struct wclap_event_midi2 {
   wclap_event_header_t header;

   uint16_t port_index;
   uint32_t data[4];
};
struct wclap_input_events {
   Pointer<void> ctx;
   Function<uint32_t,Pointer<const struct wclap_input_events> list> size;
   Function<Pointer<const wclap_event_header_t> ,Pointer<const struct wclap_input_events> list, uint32_t index> get;
};
struct wclap_output_events {
   Pointer<void> ctx;
   Function<bool,Pointer<const struct wclap_output_events> list,
                            Pointer<const wclap_event_header_t>       event> try_push;
};
struct wclap_audio_buffer {
   Pointer<Pointer<float>>  data32;
   Pointer<Pointer<double>> data64;
   uint32_t channel_count;
   uint32_t latency;
   uint64_t constant_mask;
};
typedef int32_t wclap_process_status;
struct wclap_process {
   int64_t steady_time;
   uint32_t frames_count;
   Pointer<const wclap_event_transport_t> transport;
   Pointer<const wclap_audio_buffer_t> audio_inputs;
   Pointer<wclap_audio_buffer_t>       audio_outputs;
   uint32_t                   audio_inputs_count;
   uint32_t                   audio_outputs_count;
   Pointer<const wclap_input_events_t>  in_events;
   Pointer<const wclap_output_events_t> out_events;
};
struct wclap_plugin_descriptor {
   wclap_version_t wclap_version;
   Pointer<const char> id;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> manual_url;
   Pointer<const char> support_url;
   Pointer<const char> version;
   Pointer<const char> description;
   Pointer<const char> Pointer<const> features;
};
struct wclap_plugin {
   Pointer<const wclap_plugin_descriptor_t> desc;

   Pointer<void> plugin_data;
   Function<bool,Pointer<const struct wclap_plugin> plugin> init;
   Function<void,Pointer<const struct wclap_plugin> plugin> destroy;
   Function<bool,Pointer<const struct wclap_plugin> plugin,
                            double                    sample_rate,
                            uint32_t                  min_frames_count,
                            uint32_t                  max_frames_count> activate;
   Function<void,Pointer<const struct wclap_plugin> plugin> deactivate;
   Function<bool,Pointer<const struct wclap_plugin> plugin> start_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> stop_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> reset;
   Function<wclap_process_status,Pointer<const struct wclap_plugin> plugin,
                                          Pointer<const wclap_process_t>     process> process;
   Function<Pointer<const void> ,Pointer<const struct wclap_plugin> plugin, Pointer<const char> id> get_extension;
   Function<void,Pointer<const struct wclap_plugin> plugin> on_main_thread;
};
struct wclap_plugin_preset_load {
   Function<bool,Pointer<const wclap_plugin_t> plugin,
                                 uint32_t             location_kind,
                                 Pointer<const char>          location,
                                 Pointer<const char>          load_key> from_location;
};
struct wclap_host_preset_load {
   Function<void,Pointer<const wclap_host_t> host,
                            uint32_t           location_kind,
                            Pointer<const char>        location,
                            Pointer<const char>        load_key,
                            int32_t            os_error,
                            Pointer<const char>        msg> on_error;
   Function<void,Pointer<const wclap_host_t> host,
                          uint32_t           location_kind,
                          Pointer<const char>        location,
                          Pointer<const char>        load_key> loaded;
};
struct wclap_version {
   uint32_t major;
   uint32_t minor;
   uint32_t revision;
};
struct wclap_host {
   wclap_version_t wclap_version;

   Pointer<void> host_data;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> version;
   Function<Pointer<const void> ,Pointer<const struct wclap_host> host, Pointer<const char> extension_id> get_extension;
   Function<void,Pointer<const struct wclap_host> host> request_restart;
   Function<void,Pointer<const struct wclap_host> host> request_process;
   Function<void,Pointer<const struct wclap_host> host> request_callback;
};
typedef int64_t wclap_beattime;
typedef int64_t wclap_sectime;
typedef uint32_t wclap_id;
typedef int32_t wclap_note_expression;
struct wclap_event_header {
   uint32_t size;
   uint32_t time;
   uint16_t space_id;
   uint16_t type;
   uint32_t flags;
};
struct wclap_event_note {
   wclap_event_header_t header;

   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;
   double  velocity;
};
struct wclap_event_note_expression {
   wclap_event_header_t header;

   wclap_note_expression expression_id;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_value {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_mod {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double amount;
};
struct wclap_event_param_gesture {
   wclap_event_header_t header;
   wclap_id param_id;
};
struct wclap_event_transport {
   wclap_event_header_t header;

   uint32_t flags;

   wclap_beattime song_pos_beats;
   wclap_sectime  song_pos_seconds;

   double tempo;
   double tempo_inc;

   wclap_beattime loop_start_beats;
   wclap_beattime loop_end_beats;
   wclap_sectime  loop_start_seconds;
   wclap_sectime  loop_end_seconds;

   wclap_beattime bar_start;
   int32_t       bar_number;

   uint16_t tsig_num;
   uint16_t tsig_denom;
};
struct wclap_event_midi {
   wclap_event_header_t header;

   uint16_t port_index;
   uint8_t  data[3];
};
struct wclap_event_midi_sysex {
   wclap_event_header_t header;

   uint16_t       port_index;
   Pointer<const uint8_t> buffer;
   uint32_t       size;
};
struct wclap_event_midi2 {
   wclap_event_header_t header;

   uint16_t port_index;
   uint32_t data[4];
};
struct wclap_input_events {
   Pointer<void> ctx;
   Function<uint32_t,Pointer<const struct wclap_input_events> list> size;
   Function<Pointer<const wclap_event_header_t> ,Pointer<const struct wclap_input_events> list, uint32_t index> get;
};
struct wclap_output_events {
   Pointer<void> ctx;
   Function<bool,Pointer<const struct wclap_output_events> list,
                            Pointer<const wclap_event_header_t>       event> try_push;
};
struct wclap_audio_buffer {
   Pointer<Pointer<float>>  data32;
   Pointer<Pointer<double>> data64;
   uint32_t channel_count;
   uint32_t latency;
   uint64_t constant_mask;
};
typedef int32_t wclap_process_status;
struct wclap_process {
   int64_t steady_time;
   uint32_t frames_count;
   Pointer<const wclap_event_transport_t> transport;
   Pointer<const wclap_audio_buffer_t> audio_inputs;
   Pointer<wclap_audio_buffer_t>       audio_outputs;
   uint32_t                   audio_inputs_count;
   uint32_t                   audio_outputs_count;
   Pointer<const wclap_input_events_t>  in_events;
   Pointer<const wclap_output_events_t> out_events;
};
struct wclap_plugin_descriptor {
   wclap_version_t wclap_version;
   Pointer<const char> id;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> manual_url;
   Pointer<const char> support_url;
   Pointer<const char> version;
   Pointer<const char> description;
   Pointer<const char> Pointer<const> features;
};
struct wclap_plugin {
   Pointer<const wclap_plugin_descriptor_t> desc;

   Pointer<void> plugin_data;
   Function<bool,Pointer<const struct wclap_plugin> plugin> init;
   Function<void,Pointer<const struct wclap_plugin> plugin> destroy;
   Function<bool,Pointer<const struct wclap_plugin> plugin,
                            double                    sample_rate,
                            uint32_t                  min_frames_count,
                            uint32_t                  max_frames_count> activate;
   Function<void,Pointer<const struct wclap_plugin> plugin> deactivate;
   Function<bool,Pointer<const struct wclap_plugin> plugin> start_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> stop_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> reset;
   Function<wclap_process_status,Pointer<const struct wclap_plugin> plugin,
                                          Pointer<const wclap_process_t>     process> process;
   Function<Pointer<const void> ,Pointer<const struct wclap_plugin> plugin, Pointer<const char> id> get_extension;
   Function<void,Pointer<const struct wclap_plugin> plugin> on_main_thread;
};
struct wclap_remote_controls_page {
   char    section_name[CLAP_NAME_SIZE];
   wclap_id page_id;
   char    page_name[CLAP_NAME_SIZE];
   wclap_id param_ids[CLAP_REMOTE_CONTROLS_COUNT];
   bool is_for_preset;
};
struct wclap_plugin_remote_controls {
   Function<uint32_t,Pointer<const wclap_plugin_t> plugin> count;
   Function<bool,Pointer<const wclap_plugin_t>         plugin,
                       uint32_t                     page_index,
                       Pointer<wclap_remote_controls_page_t> page> get;
};
struct wclap_host_remote_controls {
   Function<void,Pointer<const wclap_host_t> host> changed;
   Function<void,Pointer<const wclap_host_t> host, wclap_id page_id> suggest_page;
};
struct wclap_version {
   uint32_t major;
   uint32_t minor;
   uint32_t revision;
};
struct wclap_host {
   wclap_version_t wclap_version;

   Pointer<void> host_data;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> version;
   Function<Pointer<const void> ,Pointer<const struct wclap_host> host, Pointer<const char> extension_id> get_extension;
   Function<void,Pointer<const struct wclap_host> host> request_restart;
   Function<void,Pointer<const struct wclap_host> host> request_process;
   Function<void,Pointer<const struct wclap_host> host> request_callback;
};
typedef int64_t wclap_beattime;
typedef int64_t wclap_sectime;
typedef uint32_t wclap_id;
typedef int32_t wclap_note_expression;
struct wclap_event_header {
   uint32_t size;
   uint32_t time;
   uint16_t space_id;
   uint16_t type;
   uint32_t flags;
};
struct wclap_event_note {
   wclap_event_header_t header;

   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;
   double  velocity;
};
struct wclap_event_note_expression {
   wclap_event_header_t header;

   wclap_note_expression expression_id;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_value {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_mod {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double amount;
};
struct wclap_event_param_gesture {
   wclap_event_header_t header;
   wclap_id param_id;
};
struct wclap_event_transport {
   wclap_event_header_t header;

   uint32_t flags;

   wclap_beattime song_pos_beats;
   wclap_sectime  song_pos_seconds;

   double tempo;
   double tempo_inc;

   wclap_beattime loop_start_beats;
   wclap_beattime loop_end_beats;
   wclap_sectime  loop_start_seconds;
   wclap_sectime  loop_end_seconds;

   wclap_beattime bar_start;
   int32_t       bar_number;

   uint16_t tsig_num;
   uint16_t tsig_denom;
};
struct wclap_event_midi {
   wclap_event_header_t header;

   uint16_t port_index;
   uint8_t  data[3];
};
struct wclap_event_midi_sysex {
   wclap_event_header_t header;

   uint16_t       port_index;
   Pointer<const uint8_t> buffer;
   uint32_t       size;
};
struct wclap_event_midi2 {
   wclap_event_header_t header;

   uint16_t port_index;
   uint32_t data[4];
};
struct wclap_input_events {
   Pointer<void> ctx;
   Function<uint32_t,Pointer<const struct wclap_input_events> list> size;
   Function<Pointer<const wclap_event_header_t> ,Pointer<const struct wclap_input_events> list, uint32_t index> get;
};
struct wclap_output_events {
   Pointer<void> ctx;
   Function<bool,Pointer<const struct wclap_output_events> list,
                            Pointer<const wclap_event_header_t>       event> try_push;
};
struct wclap_audio_buffer {
   Pointer<Pointer<float>>  data32;
   Pointer<Pointer<double>> data64;
   uint32_t channel_count;
   uint32_t latency;
   uint64_t constant_mask;
};
typedef int32_t wclap_process_status;
struct wclap_process {
   int64_t steady_time;
   uint32_t frames_count;
   Pointer<const wclap_event_transport_t> transport;
   Pointer<const wclap_audio_buffer_t> audio_inputs;
   Pointer<wclap_audio_buffer_t>       audio_outputs;
   uint32_t                   audio_inputs_count;
   uint32_t                   audio_outputs_count;
   Pointer<const wclap_input_events_t>  in_events;
   Pointer<const wclap_output_events_t> out_events;
};
struct wclap_plugin_descriptor {
   wclap_version_t wclap_version;
   Pointer<const char> id;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> manual_url;
   Pointer<const char> support_url;
   Pointer<const char> version;
   Pointer<const char> description;
   Pointer<const char> Pointer<const> features;
};
struct wclap_plugin {
   Pointer<const wclap_plugin_descriptor_t> desc;

   Pointer<void> plugin_data;
   Function<bool,Pointer<const struct wclap_plugin> plugin> init;
   Function<void,Pointer<const struct wclap_plugin> plugin> destroy;
   Function<bool,Pointer<const struct wclap_plugin> plugin,
                            double                    sample_rate,
                            uint32_t                  min_frames_count,
                            uint32_t                  max_frames_count> activate;
   Function<void,Pointer<const struct wclap_plugin> plugin> deactivate;
   Function<bool,Pointer<const struct wclap_plugin> plugin> start_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> stop_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> reset;
   Function<wclap_process_status,Pointer<const struct wclap_plugin> plugin,
                                          Pointer<const wclap_process_t>     process> process;
   Function<Pointer<const void> ,Pointer<const struct wclap_plugin> plugin, Pointer<const char> id> get_extension;
   Function<void,Pointer<const struct wclap_plugin> plugin> on_main_thread;
};
typedef int32_t wclap_plugin_render_mode;
struct wclap_plugin_render {
   Function<bool,Pointer<const wclap_plugin_t> plugin> has_hard_realtime_requirement;
   Function<bool,Pointer<const wclap_plugin_t> plugin, wclap_plugin_render_mode mode> set;
};
struct wclap_version {
   uint32_t major;
   uint32_t minor;
   uint32_t revision;
};
struct wclap_host {
   wclap_version_t wclap_version;

   Pointer<void> host_data;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> version;
   Function<Pointer<const void> ,Pointer<const struct wclap_host> host, Pointer<const char> extension_id> get_extension;
   Function<void,Pointer<const struct wclap_host> host> request_restart;
   Function<void,Pointer<const struct wclap_host> host> request_process;
   Function<void,Pointer<const struct wclap_host> host> request_callback;
};
typedef int64_t wclap_beattime;
typedef int64_t wclap_sectime;
typedef uint32_t wclap_id;
typedef int32_t wclap_note_expression;
struct wclap_event_header {
   uint32_t size;
   uint32_t time;
   uint16_t space_id;
   uint16_t type;
   uint32_t flags;
};
struct wclap_event_note {
   wclap_event_header_t header;

   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;
   double  velocity;
};
struct wclap_event_note_expression {
   wclap_event_header_t header;

   wclap_note_expression expression_id;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_value {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_mod {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double amount;
};
struct wclap_event_param_gesture {
   wclap_event_header_t header;
   wclap_id param_id;
};
struct wclap_event_transport {
   wclap_event_header_t header;

   uint32_t flags;

   wclap_beattime song_pos_beats;
   wclap_sectime  song_pos_seconds;

   double tempo;
   double tempo_inc;

   wclap_beattime loop_start_beats;
   wclap_beattime loop_end_beats;
   wclap_sectime  loop_start_seconds;
   wclap_sectime  loop_end_seconds;

   wclap_beattime bar_start;
   int32_t       bar_number;

   uint16_t tsig_num;
   uint16_t tsig_denom;
};
struct wclap_event_midi {
   wclap_event_header_t header;

   uint16_t port_index;
   uint8_t  data[3];
};
struct wclap_event_midi_sysex {
   wclap_event_header_t header;

   uint16_t       port_index;
   Pointer<const uint8_t> buffer;
   uint32_t       size;
};
struct wclap_event_midi2 {
   wclap_event_header_t header;

   uint16_t port_index;
   uint32_t data[4];
};
struct wclap_input_events {
   Pointer<void> ctx;
   Function<uint32_t,Pointer<const struct wclap_input_events> list> size;
   Function<Pointer<const wclap_event_header_t> ,Pointer<const struct wclap_input_events> list, uint32_t index> get;
};
struct wclap_output_events {
   Pointer<void> ctx;
   Function<bool,Pointer<const struct wclap_output_events> list,
                            Pointer<const wclap_event_header_t>       event> try_push;
};
struct wclap_audio_buffer {
   Pointer<Pointer<float>>  data32;
   Pointer<Pointer<double>> data64;
   uint32_t channel_count;
   uint32_t latency;
   uint64_t constant_mask;
};
typedef int32_t wclap_process_status;
struct wclap_process {
   int64_t steady_time;
   uint32_t frames_count;
   Pointer<const wclap_event_transport_t> transport;
   Pointer<const wclap_audio_buffer_t> audio_inputs;
   Pointer<wclap_audio_buffer_t>       audio_outputs;
   uint32_t                   audio_inputs_count;
   uint32_t                   audio_outputs_count;
   Pointer<const wclap_input_events_t>  in_events;
   Pointer<const wclap_output_events_t> out_events;
};
struct wclap_plugin_descriptor {
   wclap_version_t wclap_version;
   Pointer<const char> id;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> manual_url;
   Pointer<const char> support_url;
   Pointer<const char> version;
   Pointer<const char> description;
   Pointer<const char> Pointer<const> features;
};
struct wclap_plugin {
   Pointer<const wclap_plugin_descriptor_t> desc;

   Pointer<void> plugin_data;
   Function<bool,Pointer<const struct wclap_plugin> plugin> init;
   Function<void,Pointer<const struct wclap_plugin> plugin> destroy;
   Function<bool,Pointer<const struct wclap_plugin> plugin,
                            double                    sample_rate,
                            uint32_t                  min_frames_count,
                            uint32_t                  max_frames_count> activate;
   Function<void,Pointer<const struct wclap_plugin> plugin> deactivate;
   Function<bool,Pointer<const struct wclap_plugin> plugin> start_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> stop_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> reset;
   Function<wclap_process_status,Pointer<const struct wclap_plugin> plugin,
                                          Pointer<const wclap_process_t>     process> process;
   Function<Pointer<const void> ,Pointer<const struct wclap_plugin> plugin, Pointer<const char> id> get_extension;
   Function<void,Pointer<const struct wclap_plugin> plugin> on_main_thread;
};
struct wclap_istream {
   Pointer<void> ctx;
   Function<int64_t,Pointer<const struct wclap_istream> stream, Pointer<void> buffer, uint64_t size> read;
};
struct wclap_ostream {
   Pointer<void> ctx;
   Function<int64_t,Pointer<const struct wclap_ostream> stream, Pointer<const void> buffer, uint64_t size> write;
};
struct wclap_plugin_state_context {
   Function<bool,Pointer<const wclap_plugin_t>  plugin,
                        Pointer<const wclap_ostream_t> stream,
                        uint32_t              context_type> save;
   Function<bool,Pointer<const wclap_plugin_t>  plugin,
                        Pointer<const wclap_istream_t> stream,
                        uint32_t              context_type> load;
};
struct wclap_version {
   uint32_t major;
   uint32_t minor;
   uint32_t revision;
};
struct wclap_host {
   wclap_version_t wclap_version;

   Pointer<void> host_data;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> version;
   Function<Pointer<const void> ,Pointer<const struct wclap_host> host, Pointer<const char> extension_id> get_extension;
   Function<void,Pointer<const struct wclap_host> host> request_restart;
   Function<void,Pointer<const struct wclap_host> host> request_process;
   Function<void,Pointer<const struct wclap_host> host> request_callback;
};
typedef int64_t wclap_beattime;
typedef int64_t wclap_sectime;
typedef uint32_t wclap_id;
typedef int32_t wclap_note_expression;
struct wclap_event_header {
   uint32_t size;
   uint32_t time;
   uint16_t space_id;
   uint16_t type;
   uint32_t flags;
};
struct wclap_event_note {
   wclap_event_header_t header;

   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;
   double  velocity;
};
struct wclap_event_note_expression {
   wclap_event_header_t header;

   wclap_note_expression expression_id;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_value {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_mod {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double amount;
};
struct wclap_event_param_gesture {
   wclap_event_header_t header;
   wclap_id param_id;
};
struct wclap_event_transport {
   wclap_event_header_t header;

   uint32_t flags;

   wclap_beattime song_pos_beats;
   wclap_sectime  song_pos_seconds;

   double tempo;
   double tempo_inc;

   wclap_beattime loop_start_beats;
   wclap_beattime loop_end_beats;
   wclap_sectime  loop_start_seconds;
   wclap_sectime  loop_end_seconds;

   wclap_beattime bar_start;
   int32_t       bar_number;

   uint16_t tsig_num;
   uint16_t tsig_denom;
};
struct wclap_event_midi {
   wclap_event_header_t header;

   uint16_t port_index;
   uint8_t  data[3];
};
struct wclap_event_midi_sysex {
   wclap_event_header_t header;

   uint16_t       port_index;
   Pointer<const uint8_t> buffer;
   uint32_t       size;
};
struct wclap_event_midi2 {
   wclap_event_header_t header;

   uint16_t port_index;
   uint32_t data[4];
};
struct wclap_input_events {
   Pointer<void> ctx;
   Function<uint32_t,Pointer<const struct wclap_input_events> list> size;
   Function<Pointer<const wclap_event_header_t> ,Pointer<const struct wclap_input_events> list, uint32_t index> get;
};
struct wclap_output_events {
   Pointer<void> ctx;
   Function<bool,Pointer<const struct wclap_output_events> list,
                            Pointer<const wclap_event_header_t>       event> try_push;
};
struct wclap_audio_buffer {
   Pointer<Pointer<float>>  data32;
   Pointer<Pointer<double>> data64;
   uint32_t channel_count;
   uint32_t latency;
   uint64_t constant_mask;
};
typedef int32_t wclap_process_status;
struct wclap_process {
   int64_t steady_time;
   uint32_t frames_count;
   Pointer<const wclap_event_transport_t> transport;
   Pointer<const wclap_audio_buffer_t> audio_inputs;
   Pointer<wclap_audio_buffer_t>       audio_outputs;
   uint32_t                   audio_inputs_count;
   uint32_t                   audio_outputs_count;
   Pointer<const wclap_input_events_t>  in_events;
   Pointer<const wclap_output_events_t> out_events;
};
struct wclap_plugin_descriptor {
   wclap_version_t wclap_version;
   Pointer<const char> id;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> manual_url;
   Pointer<const char> support_url;
   Pointer<const char> version;
   Pointer<const char> description;
   Pointer<const char> Pointer<const> features;
};
struct wclap_plugin {
   Pointer<const wclap_plugin_descriptor_t> desc;

   Pointer<void> plugin_data;
   Function<bool,Pointer<const struct wclap_plugin> plugin> init;
   Function<void,Pointer<const struct wclap_plugin> plugin> destroy;
   Function<bool,Pointer<const struct wclap_plugin> plugin,
                            double                    sample_rate,
                            uint32_t                  min_frames_count,
                            uint32_t                  max_frames_count> activate;
   Function<void,Pointer<const struct wclap_plugin> plugin> deactivate;
   Function<bool,Pointer<const struct wclap_plugin> plugin> start_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> stop_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> reset;
   Function<wclap_process_status,Pointer<const struct wclap_plugin> plugin,
                                          Pointer<const wclap_process_t>     process> process;
   Function<Pointer<const void> ,Pointer<const struct wclap_plugin> plugin, Pointer<const char> id> get_extension;
   Function<void,Pointer<const struct wclap_plugin> plugin> on_main_thread;
};
struct wclap_istream {
   Pointer<void> ctx;
   Function<int64_t,Pointer<const struct wclap_istream> stream, Pointer<void> buffer, uint64_t size> read;
};
struct wclap_ostream {
   Pointer<void> ctx;
   Function<int64_t,Pointer<const struct wclap_ostream> stream, Pointer<const void> buffer, uint64_t size> write;
};
struct wclap_plugin_state {
   Function<bool,Pointer<const wclap_plugin_t> plugin, Pointer<const wclap_ostream_t> stream> save;
   Function<bool,Pointer<const wclap_plugin_t> plugin, Pointer<const wclap_istream_t> stream> load;
};
struct wclap_host_state {
   Function<void,Pointer<const wclap_host_t> host> mark_dirty;
};
struct wclap_version {
   uint32_t major;
   uint32_t minor;
   uint32_t revision;
};
struct wclap_host {
   wclap_version_t wclap_version;

   Pointer<void> host_data;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> version;
   Function<Pointer<const void> ,Pointer<const struct wclap_host> host, Pointer<const char> extension_id> get_extension;
   Function<void,Pointer<const struct wclap_host> host> request_restart;
   Function<void,Pointer<const struct wclap_host> host> request_process;
   Function<void,Pointer<const struct wclap_host> host> request_callback;
};
typedef int64_t wclap_beattime;
typedef int64_t wclap_sectime;
typedef uint32_t wclap_id;
typedef int32_t wclap_note_expression;
struct wclap_event_header {
   uint32_t size;
   uint32_t time;
   uint16_t space_id;
   uint16_t type;
   uint32_t flags;
};
struct wclap_event_note {
   wclap_event_header_t header;

   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;
   double  velocity;
};
struct wclap_event_note_expression {
   wclap_event_header_t header;

   wclap_note_expression expression_id;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_value {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_mod {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double amount;
};
struct wclap_event_param_gesture {
   wclap_event_header_t header;
   wclap_id param_id;
};
struct wclap_event_transport {
   wclap_event_header_t header;

   uint32_t flags;

   wclap_beattime song_pos_beats;
   wclap_sectime  song_pos_seconds;

   double tempo;
   double tempo_inc;

   wclap_beattime loop_start_beats;
   wclap_beattime loop_end_beats;
   wclap_sectime  loop_start_seconds;
   wclap_sectime  loop_end_seconds;

   wclap_beattime bar_start;
   int32_t       bar_number;

   uint16_t tsig_num;
   uint16_t tsig_denom;
};
struct wclap_event_midi {
   wclap_event_header_t header;

   uint16_t port_index;
   uint8_t  data[3];
};
struct wclap_event_midi_sysex {
   wclap_event_header_t header;

   uint16_t       port_index;
   Pointer<const uint8_t> buffer;
   uint32_t       size;
};
struct wclap_event_midi2 {
   wclap_event_header_t header;

   uint16_t port_index;
   uint32_t data[4];
};
struct wclap_input_events {
   Pointer<void> ctx;
   Function<uint32_t,Pointer<const struct wclap_input_events> list> size;
   Function<Pointer<const wclap_event_header_t> ,Pointer<const struct wclap_input_events> list, uint32_t index> get;
};
struct wclap_output_events {
   Pointer<void> ctx;
   Function<bool,Pointer<const struct wclap_output_events> list,
                            Pointer<const wclap_event_header_t>       event> try_push;
};
struct wclap_audio_buffer {
   Pointer<Pointer<float>>  data32;
   Pointer<Pointer<double>> data64;
   uint32_t channel_count;
   uint32_t latency;
   uint64_t constant_mask;
};
typedef int32_t wclap_process_status;
struct wclap_process {
   int64_t steady_time;
   uint32_t frames_count;
   Pointer<const wclap_event_transport_t> transport;
   Pointer<const wclap_audio_buffer_t> audio_inputs;
   Pointer<wclap_audio_buffer_t>       audio_outputs;
   uint32_t                   audio_inputs_count;
   uint32_t                   audio_outputs_count;
   Pointer<const wclap_input_events_t>  in_events;
   Pointer<const wclap_output_events_t> out_events;
};
struct wclap_plugin_descriptor {
   wclap_version_t wclap_version;
   Pointer<const char> id;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> manual_url;
   Pointer<const char> support_url;
   Pointer<const char> version;
   Pointer<const char> description;
   Pointer<const char> Pointer<const> features;
};
struct wclap_plugin {
   Pointer<const wclap_plugin_descriptor_t> desc;

   Pointer<void> plugin_data;
   Function<bool,Pointer<const struct wclap_plugin> plugin> init;
   Function<void,Pointer<const struct wclap_plugin> plugin> destroy;
   Function<bool,Pointer<const struct wclap_plugin> plugin,
                            double                    sample_rate,
                            uint32_t                  min_frames_count,
                            uint32_t                  max_frames_count> activate;
   Function<void,Pointer<const struct wclap_plugin> plugin> deactivate;
   Function<bool,Pointer<const struct wclap_plugin> plugin> start_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> stop_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> reset;
   Function<wclap_process_status,Pointer<const struct wclap_plugin> plugin,
                                          Pointer<const wclap_process_t>     process> process;
   Function<Pointer<const void> ,Pointer<const struct wclap_plugin> plugin, Pointer<const char> id> get_extension;
   Function<void,Pointer<const struct wclap_plugin> plugin> on_main_thread;
};
struct wclap_plugin_surround {
   Function<bool,Pointer<const wclap_plugin_t> plugin, uint64_t channel_mask> is_channel_mask_supported;
   Function<uint32_t,Pointer<const wclap_plugin_t> plugin,
                                       bool                 is_input,
                                       uint32_t             port_index,
                                       Pointer<uint8_t>             channel_map,
                                       uint32_t             channel_map_capacity> get_channel_map;
};
struct wclap_host_surround {
   Function<void,Pointer<const wclap_host_t> host> changed;
};
struct wclap_version {
   uint32_t major;
   uint32_t minor;
   uint32_t revision;
};
struct wclap_host {
   wclap_version_t wclap_version;

   Pointer<void> host_data;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> version;
   Function<Pointer<const void> ,Pointer<const struct wclap_host> host, Pointer<const char> extension_id> get_extension;
   Function<void,Pointer<const struct wclap_host> host> request_restart;
   Function<void,Pointer<const struct wclap_host> host> request_process;
   Function<void,Pointer<const struct wclap_host> host> request_callback;
};
typedef int64_t wclap_beattime;
typedef int64_t wclap_sectime;
typedef uint32_t wclap_id;
typedef int32_t wclap_note_expression;
struct wclap_event_header {
   uint32_t size;
   uint32_t time;
   uint16_t space_id;
   uint16_t type;
   uint32_t flags;
};
struct wclap_event_note {
   wclap_event_header_t header;

   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;
   double  velocity;
};
struct wclap_event_note_expression {
   wclap_event_header_t header;

   wclap_note_expression expression_id;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_value {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_mod {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double amount;
};
struct wclap_event_param_gesture {
   wclap_event_header_t header;
   wclap_id param_id;
};
struct wclap_event_transport {
   wclap_event_header_t header;

   uint32_t flags;

   wclap_beattime song_pos_beats;
   wclap_sectime  song_pos_seconds;

   double tempo;
   double tempo_inc;

   wclap_beattime loop_start_beats;
   wclap_beattime loop_end_beats;
   wclap_sectime  loop_start_seconds;
   wclap_sectime  loop_end_seconds;

   wclap_beattime bar_start;
   int32_t       bar_number;

   uint16_t tsig_num;
   uint16_t tsig_denom;
};
struct wclap_event_midi {
   wclap_event_header_t header;

   uint16_t port_index;
   uint8_t  data[3];
};
struct wclap_event_midi_sysex {
   wclap_event_header_t header;

   uint16_t       port_index;
   Pointer<const uint8_t> buffer;
   uint32_t       size;
};
struct wclap_event_midi2 {
   wclap_event_header_t header;

   uint16_t port_index;
   uint32_t data[4];
};
struct wclap_input_events {
   Pointer<void> ctx;
   Function<uint32_t,Pointer<const struct wclap_input_events> list> size;
   Function<Pointer<const wclap_event_header_t> ,Pointer<const struct wclap_input_events> list, uint32_t index> get;
};
struct wclap_output_events {
   Pointer<void> ctx;
   Function<bool,Pointer<const struct wclap_output_events> list,
                            Pointer<const wclap_event_header_t>       event> try_push;
};
struct wclap_audio_buffer {
   Pointer<Pointer<float>>  data32;
   Pointer<Pointer<double>> data64;
   uint32_t channel_count;
   uint32_t latency;
   uint64_t constant_mask;
};
typedef int32_t wclap_process_status;
struct wclap_process {
   int64_t steady_time;
   uint32_t frames_count;
   Pointer<const wclap_event_transport_t> transport;
   Pointer<const wclap_audio_buffer_t> audio_inputs;
   Pointer<wclap_audio_buffer_t>       audio_outputs;
   uint32_t                   audio_inputs_count;
   uint32_t                   audio_outputs_count;
   Pointer<const wclap_input_events_t>  in_events;
   Pointer<const wclap_output_events_t> out_events;
};
struct wclap_plugin_descriptor {
   wclap_version_t wclap_version;
   Pointer<const char> id;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> manual_url;
   Pointer<const char> support_url;
   Pointer<const char> version;
   Pointer<const char> description;
   Pointer<const char> Pointer<const> features;
};
struct wclap_plugin {
   Pointer<const wclap_plugin_descriptor_t> desc;

   Pointer<void> plugin_data;
   Function<bool,Pointer<const struct wclap_plugin> plugin> init;
   Function<void,Pointer<const struct wclap_plugin> plugin> destroy;
   Function<bool,Pointer<const struct wclap_plugin> plugin,
                            double                    sample_rate,
                            uint32_t                  min_frames_count,
                            uint32_t                  max_frames_count> activate;
   Function<void,Pointer<const struct wclap_plugin> plugin> deactivate;
   Function<bool,Pointer<const struct wclap_plugin> plugin> start_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> stop_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> reset;
   Function<wclap_process_status,Pointer<const struct wclap_plugin> plugin,
                                          Pointer<const wclap_process_t>     process> process;
   Function<Pointer<const void> ,Pointer<const struct wclap_plugin> plugin, Pointer<const char> id> get_extension;
   Function<void,Pointer<const struct wclap_plugin> plugin> on_main_thread;
};
struct wclap_plugin_tail {
   Function<uint32_t,Pointer<const wclap_plugin_t> plugin> get;
};
struct wclap_host_tail {
   Function<void,Pointer<const wclap_host_t> host> changed;
};
struct wclap_version {
   uint32_t major;
   uint32_t minor;
   uint32_t revision;
};
struct wclap_host {
   wclap_version_t wclap_version;

   Pointer<void> host_data;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> version;
   Function<Pointer<const void> ,Pointer<const struct wclap_host> host, Pointer<const char> extension_id> get_extension;
   Function<void,Pointer<const struct wclap_host> host> request_restart;
   Function<void,Pointer<const struct wclap_host> host> request_process;
   Function<void,Pointer<const struct wclap_host> host> request_callback;
};
typedef int64_t wclap_beattime;
typedef int64_t wclap_sectime;
typedef uint32_t wclap_id;
typedef int32_t wclap_note_expression;
struct wclap_event_header {
   uint32_t size;
   uint32_t time;
   uint16_t space_id;
   uint16_t type;
   uint32_t flags;
};
struct wclap_event_note {
   wclap_event_header_t header;

   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;
   double  velocity;
};
struct wclap_event_note_expression {
   wclap_event_header_t header;

   wclap_note_expression expression_id;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_value {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_mod {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double amount;
};
struct wclap_event_param_gesture {
   wclap_event_header_t header;
   wclap_id param_id;
};
struct wclap_event_transport {
   wclap_event_header_t header;

   uint32_t flags;

   wclap_beattime song_pos_beats;
   wclap_sectime  song_pos_seconds;

   double tempo;
   double tempo_inc;

   wclap_beattime loop_start_beats;
   wclap_beattime loop_end_beats;
   wclap_sectime  loop_start_seconds;
   wclap_sectime  loop_end_seconds;

   wclap_beattime bar_start;
   int32_t       bar_number;

   uint16_t tsig_num;
   uint16_t tsig_denom;
};
struct wclap_event_midi {
   wclap_event_header_t header;

   uint16_t port_index;
   uint8_t  data[3];
};
struct wclap_event_midi_sysex {
   wclap_event_header_t header;

   uint16_t       port_index;
   Pointer<const uint8_t> buffer;
   uint32_t       size;
};
struct wclap_event_midi2 {
   wclap_event_header_t header;

   uint16_t port_index;
   uint32_t data[4];
};
struct wclap_input_events {
   Pointer<void> ctx;
   Function<uint32_t,Pointer<const struct wclap_input_events> list> size;
   Function<Pointer<const wclap_event_header_t> ,Pointer<const struct wclap_input_events> list, uint32_t index> get;
};
struct wclap_output_events {
   Pointer<void> ctx;
   Function<bool,Pointer<const struct wclap_output_events> list,
                            Pointer<const wclap_event_header_t>       event> try_push;
};
struct wclap_audio_buffer {
   Pointer<Pointer<float>>  data32;
   Pointer<Pointer<double>> data64;
   uint32_t channel_count;
   uint32_t latency;
   uint64_t constant_mask;
};
typedef int32_t wclap_process_status;
struct wclap_process {
   int64_t steady_time;
   uint32_t frames_count;
   Pointer<const wclap_event_transport_t> transport;
   Pointer<const wclap_audio_buffer_t> audio_inputs;
   Pointer<wclap_audio_buffer_t>       audio_outputs;
   uint32_t                   audio_inputs_count;
   uint32_t                   audio_outputs_count;
   Pointer<const wclap_input_events_t>  in_events;
   Pointer<const wclap_output_events_t> out_events;
};
struct wclap_plugin_descriptor {
   wclap_version_t wclap_version;
   Pointer<const char> id;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> manual_url;
   Pointer<const char> support_url;
   Pointer<const char> version;
   Pointer<const char> description;
   Pointer<const char> Pointer<const> features;
};
struct wclap_plugin {
   Pointer<const wclap_plugin_descriptor_t> desc;

   Pointer<void> plugin_data;
   Function<bool,Pointer<const struct wclap_plugin> plugin> init;
   Function<void,Pointer<const struct wclap_plugin> plugin> destroy;
   Function<bool,Pointer<const struct wclap_plugin> plugin,
                            double                    sample_rate,
                            uint32_t                  min_frames_count,
                            uint32_t                  max_frames_count> activate;
   Function<void,Pointer<const struct wclap_plugin> plugin> deactivate;
   Function<bool,Pointer<const struct wclap_plugin> plugin> start_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> stop_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> reset;
   Function<wclap_process_status,Pointer<const struct wclap_plugin> plugin,
                                          Pointer<const wclap_process_t>     process> process;
   Function<Pointer<const void> ,Pointer<const struct wclap_plugin> plugin, Pointer<const char> id> get_extension;
   Function<void,Pointer<const struct wclap_plugin> plugin> on_main_thread;
};
struct wclap_host_thread_check {
   Function<bool,Pointer<const wclap_host_t> host> is_main_thread;
   Function<bool,Pointer<const wclap_host_t> host> is_audio_thread;
};
struct wclap_version {
   uint32_t major;
   uint32_t minor;
   uint32_t revision;
};
struct wclap_host {
   wclap_version_t wclap_version;

   Pointer<void> host_data;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> version;
   Function<Pointer<const void> ,Pointer<const struct wclap_host> host, Pointer<const char> extension_id> get_extension;
   Function<void,Pointer<const struct wclap_host> host> request_restart;
   Function<void,Pointer<const struct wclap_host> host> request_process;
   Function<void,Pointer<const struct wclap_host> host> request_callback;
};
typedef int64_t wclap_beattime;
typedef int64_t wclap_sectime;
typedef uint32_t wclap_id;
typedef int32_t wclap_note_expression;
struct wclap_event_header {
   uint32_t size;
   uint32_t time;
   uint16_t space_id;
   uint16_t type;
   uint32_t flags;
};
struct wclap_event_note {
   wclap_event_header_t header;

   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;
   double  velocity;
};
struct wclap_event_note_expression {
   wclap_event_header_t header;

   wclap_note_expression expression_id;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_value {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_mod {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double amount;
};
struct wclap_event_param_gesture {
   wclap_event_header_t header;
   wclap_id param_id;
};
struct wclap_event_transport {
   wclap_event_header_t header;

   uint32_t flags;

   wclap_beattime song_pos_beats;
   wclap_sectime  song_pos_seconds;

   double tempo;
   double tempo_inc;

   wclap_beattime loop_start_beats;
   wclap_beattime loop_end_beats;
   wclap_sectime  loop_start_seconds;
   wclap_sectime  loop_end_seconds;

   wclap_beattime bar_start;
   int32_t       bar_number;

   uint16_t tsig_num;
   uint16_t tsig_denom;
};
struct wclap_event_midi {
   wclap_event_header_t header;

   uint16_t port_index;
   uint8_t  data[3];
};
struct wclap_event_midi_sysex {
   wclap_event_header_t header;

   uint16_t       port_index;
   Pointer<const uint8_t> buffer;
   uint32_t       size;
};
struct wclap_event_midi2 {
   wclap_event_header_t header;

   uint16_t port_index;
   uint32_t data[4];
};
struct wclap_input_events {
   Pointer<void> ctx;
   Function<uint32_t,Pointer<const struct wclap_input_events> list> size;
   Function<Pointer<const wclap_event_header_t> ,Pointer<const struct wclap_input_events> list, uint32_t index> get;
};
struct wclap_output_events {
   Pointer<void> ctx;
   Function<bool,Pointer<const struct wclap_output_events> list,
                            Pointer<const wclap_event_header_t>       event> try_push;
};
struct wclap_audio_buffer {
   Pointer<Pointer<float>>  data32;
   Pointer<Pointer<double>> data64;
   uint32_t channel_count;
   uint32_t latency;
   uint64_t constant_mask;
};
typedef int32_t wclap_process_status;
struct wclap_process {
   int64_t steady_time;
   uint32_t frames_count;
   Pointer<const wclap_event_transport_t> transport;
   Pointer<const wclap_audio_buffer_t> audio_inputs;
   Pointer<wclap_audio_buffer_t>       audio_outputs;
   uint32_t                   audio_inputs_count;
   uint32_t                   audio_outputs_count;
   Pointer<const wclap_input_events_t>  in_events;
   Pointer<const wclap_output_events_t> out_events;
};
struct wclap_plugin_descriptor {
   wclap_version_t wclap_version;
   Pointer<const char> id;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> manual_url;
   Pointer<const char> support_url;
   Pointer<const char> version;
   Pointer<const char> description;
   Pointer<const char> Pointer<const> features;
};
struct wclap_plugin {
   Pointer<const wclap_plugin_descriptor_t> desc;

   Pointer<void> plugin_data;
   Function<bool,Pointer<const struct wclap_plugin> plugin> init;
   Function<void,Pointer<const struct wclap_plugin> plugin> destroy;
   Function<bool,Pointer<const struct wclap_plugin> plugin,
                            double                    sample_rate,
                            uint32_t                  min_frames_count,
                            uint32_t                  max_frames_count> activate;
   Function<void,Pointer<const struct wclap_plugin> plugin> deactivate;
   Function<bool,Pointer<const struct wclap_plugin> plugin> start_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> stop_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> reset;
   Function<wclap_process_status,Pointer<const struct wclap_plugin> plugin,
                                          Pointer<const wclap_process_t>     process> process;
   Function<Pointer<const void> ,Pointer<const struct wclap_plugin> plugin, Pointer<const char> id> get_extension;
   Function<void,Pointer<const struct wclap_plugin> plugin> on_main_thread;
};
struct wclap_plugin_thread_pool {
   Function<void,Pointer<const wclap_plugin_t> plugin, uint32_t task_index> exec;
};
struct wclap_host_thread_pool {
   Function<bool,Pointer<const wclap_host_t> host, uint32_t num_tasks> request_exec;
};
struct wclap_version {
   uint32_t major;
   uint32_t minor;
   uint32_t revision;
};
struct wclap_host {
   wclap_version_t wclap_version;

   Pointer<void> host_data;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> version;
   Function<Pointer<const void> ,Pointer<const struct wclap_host> host, Pointer<const char> extension_id> get_extension;
   Function<void,Pointer<const struct wclap_host> host> request_restart;
   Function<void,Pointer<const struct wclap_host> host> request_process;
   Function<void,Pointer<const struct wclap_host> host> request_callback;
};
typedef int64_t wclap_beattime;
typedef int64_t wclap_sectime;
typedef uint32_t wclap_id;
typedef int32_t wclap_note_expression;
struct wclap_event_header {
   uint32_t size;
   uint32_t time;
   uint16_t space_id;
   uint16_t type;
   uint32_t flags;
};
struct wclap_event_note {
   wclap_event_header_t header;

   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;
   double  velocity;
};
struct wclap_event_note_expression {
   wclap_event_header_t header;

   wclap_note_expression expression_id;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_value {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_mod {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double amount;
};
struct wclap_event_param_gesture {
   wclap_event_header_t header;
   wclap_id param_id;
};
struct wclap_event_transport {
   wclap_event_header_t header;

   uint32_t flags;

   wclap_beattime song_pos_beats;
   wclap_sectime  song_pos_seconds;

   double tempo;
   double tempo_inc;

   wclap_beattime loop_start_beats;
   wclap_beattime loop_end_beats;
   wclap_sectime  loop_start_seconds;
   wclap_sectime  loop_end_seconds;

   wclap_beattime bar_start;
   int32_t       bar_number;

   uint16_t tsig_num;
   uint16_t tsig_denom;
};
struct wclap_event_midi {
   wclap_event_header_t header;

   uint16_t port_index;
   uint8_t  data[3];
};
struct wclap_event_midi_sysex {
   wclap_event_header_t header;

   uint16_t       port_index;
   Pointer<const uint8_t> buffer;
   uint32_t       size;
};
struct wclap_event_midi2 {
   wclap_event_header_t header;

   uint16_t port_index;
   uint32_t data[4];
};
struct wclap_input_events {
   Pointer<void> ctx;
   Function<uint32_t,Pointer<const struct wclap_input_events> list> size;
   Function<Pointer<const wclap_event_header_t> ,Pointer<const struct wclap_input_events> list, uint32_t index> get;
};
struct wclap_output_events {
   Pointer<void> ctx;
   Function<bool,Pointer<const struct wclap_output_events> list,
                            Pointer<const wclap_event_header_t>       event> try_push;
};
struct wclap_audio_buffer {
   Pointer<Pointer<float>>  data32;
   Pointer<Pointer<double>> data64;
   uint32_t channel_count;
   uint32_t latency;
   uint64_t constant_mask;
};
typedef int32_t wclap_process_status;
struct wclap_process {
   int64_t steady_time;
   uint32_t frames_count;
   Pointer<const wclap_event_transport_t> transport;
   Pointer<const wclap_audio_buffer_t> audio_inputs;
   Pointer<wclap_audio_buffer_t>       audio_outputs;
   uint32_t                   audio_inputs_count;
   uint32_t                   audio_outputs_count;
   Pointer<const wclap_input_events_t>  in_events;
   Pointer<const wclap_output_events_t> out_events;
};
struct wclap_plugin_descriptor {
   wclap_version_t wclap_version;
   Pointer<const char> id;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> manual_url;
   Pointer<const char> support_url;
   Pointer<const char> version;
   Pointer<const char> description;
   Pointer<const char> Pointer<const> features;
};
struct wclap_plugin {
   Pointer<const wclap_plugin_descriptor_t> desc;

   Pointer<void> plugin_data;
   Function<bool,Pointer<const struct wclap_plugin> plugin> init;
   Function<void,Pointer<const struct wclap_plugin> plugin> destroy;
   Function<bool,Pointer<const struct wclap_plugin> plugin,
                            double                    sample_rate,
                            uint32_t                  min_frames_count,
                            uint32_t                  max_frames_count> activate;
   Function<void,Pointer<const struct wclap_plugin> plugin> deactivate;
   Function<bool,Pointer<const struct wclap_plugin> plugin> start_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> stop_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> reset;
   Function<wclap_process_status,Pointer<const struct wclap_plugin> plugin,
                                          Pointer<const wclap_process_t>     process> process;
   Function<Pointer<const void> ,Pointer<const struct wclap_plugin> plugin, Pointer<const char> id> get_extension;
   Function<void,Pointer<const struct wclap_plugin> plugin> on_main_thread;
};
struct wclap_plugin_timer_support {
   Function<void,Pointer<const wclap_plugin_t> plugin, wclap_id timer_id> on_timer;
};
struct wclap_host_timer_support {
   Function<bool,Pointer<const wclap_host_t> host, uint32_t period_ms, Pointer<wclap_id> timer_id> register_timer;
   Function<bool,Pointer<const wclap_host_t> host, wclap_id timer_id> unregister_timer;
};
struct wclap_version {
   uint32_t major;
   uint32_t minor;
   uint32_t revision;
};
struct wclap_host {
   wclap_version_t wclap_version;

   Pointer<void> host_data;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> version;
   Function<Pointer<const void> ,Pointer<const struct wclap_host> host, Pointer<const char> extension_id> get_extension;
   Function<void,Pointer<const struct wclap_host> host> request_restart;
   Function<void,Pointer<const struct wclap_host> host> request_process;
   Function<void,Pointer<const struct wclap_host> host> request_callback;
};
typedef int64_t wclap_beattime;
typedef int64_t wclap_sectime;
typedef uint32_t wclap_id;
typedef int32_t wclap_note_expression;
struct wclap_event_header {
   uint32_t size;
   uint32_t time;
   uint16_t space_id;
   uint16_t type;
   uint32_t flags;
};
struct wclap_event_note {
   wclap_event_header_t header;

   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;
   double  velocity;
};
struct wclap_event_note_expression {
   wclap_event_header_t header;

   wclap_note_expression expression_id;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_value {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_mod {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double amount;
};
struct wclap_event_param_gesture {
   wclap_event_header_t header;
   wclap_id param_id;
};
struct wclap_event_transport {
   wclap_event_header_t header;

   uint32_t flags;

   wclap_beattime song_pos_beats;
   wclap_sectime  song_pos_seconds;

   double tempo;
   double tempo_inc;

   wclap_beattime loop_start_beats;
   wclap_beattime loop_end_beats;
   wclap_sectime  loop_start_seconds;
   wclap_sectime  loop_end_seconds;

   wclap_beattime bar_start;
   int32_t       bar_number;

   uint16_t tsig_num;
   uint16_t tsig_denom;
};
struct wclap_event_midi {
   wclap_event_header_t header;

   uint16_t port_index;
   uint8_t  data[3];
};
struct wclap_event_midi_sysex {
   wclap_event_header_t header;

   uint16_t       port_index;
   Pointer<const uint8_t> buffer;
   uint32_t       size;
};
struct wclap_event_midi2 {
   wclap_event_header_t header;

   uint16_t port_index;
   uint32_t data[4];
};
struct wclap_input_events {
   Pointer<void> ctx;
   Function<uint32_t,Pointer<const struct wclap_input_events> list> size;
   Function<Pointer<const wclap_event_header_t> ,Pointer<const struct wclap_input_events> list, uint32_t index> get;
};
struct wclap_output_events {
   Pointer<void> ctx;
   Function<bool,Pointer<const struct wclap_output_events> list,
                            Pointer<const wclap_event_header_t>       event> try_push;
};
struct wclap_audio_buffer {
   Pointer<Pointer<float>>  data32;
   Pointer<Pointer<double>> data64;
   uint32_t channel_count;
   uint32_t latency;
   uint64_t constant_mask;
};
typedef int32_t wclap_process_status;
struct wclap_process {
   int64_t steady_time;
   uint32_t frames_count;
   Pointer<const wclap_event_transport_t> transport;
   Pointer<const wclap_audio_buffer_t> audio_inputs;
   Pointer<wclap_audio_buffer_t>       audio_outputs;
   uint32_t                   audio_inputs_count;
   uint32_t                   audio_outputs_count;
   Pointer<const wclap_input_events_t>  in_events;
   Pointer<const wclap_output_events_t> out_events;
};
struct wclap_plugin_descriptor {
   wclap_version_t wclap_version;
   Pointer<const char> id;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> manual_url;
   Pointer<const char> support_url;
   Pointer<const char> version;
   Pointer<const char> description;
   Pointer<const char> Pointer<const> features;
};
struct wclap_plugin {
   Pointer<const wclap_plugin_descriptor_t> desc;

   Pointer<void> plugin_data;
   Function<bool,Pointer<const struct wclap_plugin> plugin> init;
   Function<void,Pointer<const struct wclap_plugin> plugin> destroy;
   Function<bool,Pointer<const struct wclap_plugin> plugin,
                            double                    sample_rate,
                            uint32_t                  min_frames_count,
                            uint32_t                  max_frames_count> activate;
   Function<void,Pointer<const struct wclap_plugin> plugin> deactivate;
   Function<bool,Pointer<const struct wclap_plugin> plugin> start_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> stop_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> reset;
   Function<wclap_process_status,Pointer<const struct wclap_plugin> plugin,
                                          Pointer<const wclap_process_t>     process> process;
   Function<Pointer<const void> ,Pointer<const struct wclap_plugin> plugin, Pointer<const char> id> get_extension;
   Function<void,Pointer<const struct wclap_plugin> plugin> on_main_thread;
};
struct wclap_color {
   uint8_t alpha;
   uint8_t red;
   uint8_t green;
   uint8_t blue;
};
struct wclap_track_info {
   uint64_t flags;
   char name[CLAP_NAME_SIZE];
   wclap_color_t color;
   int32_t     audio_channel_count;
   Pointer<const char> audio_port_type;
};
struct wclap_plugin_track_info {
   Function<void,Pointer<const wclap_plugin_t> plugin> changed;
};
struct wclap_host_track_info {
   Function<bool,Pointer<const wclap_host_t> host, Pointer<wclap_track_info_t> info> get;
};
struct wclap_version {
   uint32_t major;
   uint32_t minor;
   uint32_t revision;
};
struct wclap_host {
   wclap_version_t wclap_version;

   Pointer<void> host_data;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> version;
   Function<Pointer<const void> ,Pointer<const struct wclap_host> host, Pointer<const char> extension_id> get_extension;
   Function<void,Pointer<const struct wclap_host> host> request_restart;
   Function<void,Pointer<const struct wclap_host> host> request_process;
   Function<void,Pointer<const struct wclap_host> host> request_callback;
};
typedef int64_t wclap_beattime;
typedef int64_t wclap_sectime;
typedef uint32_t wclap_id;
typedef int32_t wclap_note_expression;
struct wclap_event_header {
   uint32_t size;
   uint32_t time;
   uint16_t space_id;
   uint16_t type;
   uint32_t flags;
};
struct wclap_event_note {
   wclap_event_header_t header;

   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;
   double  velocity;
};
struct wclap_event_note_expression {
   wclap_event_header_t header;

   wclap_note_expression expression_id;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_value {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_mod {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double amount;
};
struct wclap_event_param_gesture {
   wclap_event_header_t header;
   wclap_id param_id;
};
struct wclap_event_transport {
   wclap_event_header_t header;

   uint32_t flags;

   wclap_beattime song_pos_beats;
   wclap_sectime  song_pos_seconds;

   double tempo;
   double tempo_inc;

   wclap_beattime loop_start_beats;
   wclap_beattime loop_end_beats;
   wclap_sectime  loop_start_seconds;
   wclap_sectime  loop_end_seconds;

   wclap_beattime bar_start;
   int32_t       bar_number;

   uint16_t tsig_num;
   uint16_t tsig_denom;
};
struct wclap_event_midi {
   wclap_event_header_t header;

   uint16_t port_index;
   uint8_t  data[3];
};
struct wclap_event_midi_sysex {
   wclap_event_header_t header;

   uint16_t       port_index;
   Pointer<const uint8_t> buffer;
   uint32_t       size;
};
struct wclap_event_midi2 {
   wclap_event_header_t header;

   uint16_t port_index;
   uint32_t data[4];
};
struct wclap_input_events {
   Pointer<void> ctx;
   Function<uint32_t,Pointer<const struct wclap_input_events> list> size;
   Function<Pointer<const wclap_event_header_t> ,Pointer<const struct wclap_input_events> list, uint32_t index> get;
};
struct wclap_output_events {
   Pointer<void> ctx;
   Function<bool,Pointer<const struct wclap_output_events> list,
                            Pointer<const wclap_event_header_t>       event> try_push;
};
struct wclap_audio_buffer {
   Pointer<Pointer<float>>  data32;
   Pointer<Pointer<double>> data64;
   uint32_t channel_count;
   uint32_t latency;
   uint64_t constant_mask;
};
typedef int32_t wclap_process_status;
struct wclap_process {
   int64_t steady_time;
   uint32_t frames_count;
   Pointer<const wclap_event_transport_t> transport;
   Pointer<const wclap_audio_buffer_t> audio_inputs;
   Pointer<wclap_audio_buffer_t>       audio_outputs;
   uint32_t                   audio_inputs_count;
   uint32_t                   audio_outputs_count;
   Pointer<const wclap_input_events_t>  in_events;
   Pointer<const wclap_output_events_t> out_events;
};
struct wclap_plugin_descriptor {
   wclap_version_t wclap_version;
   Pointer<const char> id;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> manual_url;
   Pointer<const char> support_url;
   Pointer<const char> version;
   Pointer<const char> description;
   Pointer<const char> Pointer<const> features;
};
struct wclap_plugin {
   Pointer<const wclap_plugin_descriptor_t> desc;

   Pointer<void> plugin_data;
   Function<bool,Pointer<const struct wclap_plugin> plugin> init;
   Function<void,Pointer<const struct wclap_plugin> plugin> destroy;
   Function<bool,Pointer<const struct wclap_plugin> plugin,
                            double                    sample_rate,
                            uint32_t                  min_frames_count,
                            uint32_t                  max_frames_count> activate;
   Function<void,Pointer<const struct wclap_plugin> plugin> deactivate;
   Function<bool,Pointer<const struct wclap_plugin> plugin> start_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> stop_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> reset;
   Function<wclap_process_status,Pointer<const struct wclap_plugin> plugin,
                                          Pointer<const wclap_process_t>     process> process;
   Function<Pointer<const void> ,Pointer<const struct wclap_plugin> plugin, Pointer<const char> id> get_extension;
   Function<void,Pointer<const struct wclap_plugin> plugin> on_main_thread;
};
struct wclap_voice_info {
   uint32_t voice_count;
   uint32_t voice_capacity;

   uint64_t flags;
};
struct wclap_plugin_voice_info {
   Function<bool,Pointer<const wclap_plugin_t> plugin, Pointer<wclap_voice_info_t> info> get;
};
struct wclap_host_voice_info {
   Function<void,Pointer<const wclap_host_t> host> changed;
};
struct wclap_color {
   uint8_t alpha;
   uint8_t red;
   uint8_t green;
   uint8_t blue;
};
struct wclap_version {
   uint32_t major;
   uint32_t minor;
   uint32_t revision;
};
struct wclap_plugin_entry {
   wclap_version_t wclap_version;
   Function<bool,Pointer<const char> plugin_path> init;
   Function<void,void> deinit;
   Function<Pointer<const void> ,Pointer<const char> factory_id> get_factory;
};
typedef int64_t wclap_beattime;
typedef int64_t wclap_sectime;
typedef uint32_t wclap_id;
typedef int32_t wclap_note_expression;
struct wclap_event_header {
   uint32_t size;
   uint32_t time;
   uint16_t space_id;
   uint16_t type;
   uint32_t flags;
};
struct wclap_event_note {
   wclap_event_header_t header;

   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;
   double  velocity;
};
struct wclap_event_note_expression {
   wclap_event_header_t header;

   wclap_note_expression expression_id;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_value {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_mod {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double amount;
};
struct wclap_event_param_gesture {
   wclap_event_header_t header;
   wclap_id param_id;
};
struct wclap_event_transport {
   wclap_event_header_t header;

   uint32_t flags;

   wclap_beattime song_pos_beats;
   wclap_sectime  song_pos_seconds;

   double tempo;
   double tempo_inc;

   wclap_beattime loop_start_beats;
   wclap_beattime loop_end_beats;
   wclap_sectime  loop_start_seconds;
   wclap_sectime  loop_end_seconds;

   wclap_beattime bar_start;
   int32_t       bar_number;

   uint16_t tsig_num;
   uint16_t tsig_denom;
};
struct wclap_event_midi {
   wclap_event_header_t header;

   uint16_t port_index;
   uint8_t  data[3];
};
struct wclap_event_midi_sysex {
   wclap_event_header_t header;

   uint16_t       port_index;
   Pointer<const uint8_t> buffer;
   uint32_t       size;
};
struct wclap_event_midi2 {
   wclap_event_header_t header;

   uint16_t port_index;
   uint32_t data[4];
};
struct wclap_input_events {
   Pointer<void> ctx;
   Function<uint32_t,Pointer<const struct wclap_input_events> list> size;
   Function<Pointer<const wclap_event_header_t> ,Pointer<const struct wclap_input_events> list, uint32_t index> get;
};
struct wclap_output_events {
   Pointer<void> ctx;
   Function<bool,Pointer<const struct wclap_output_events> list,
                            Pointer<const wclap_event_header_t>       event> try_push;
};
typedef int64_t wclap_beattime;
typedef int64_t wclap_sectime;
struct wclap_version {
   uint32_t major;
   uint32_t minor;
   uint32_t revision;
};
struct wclap_host {
   wclap_version_t wclap_version;

   Pointer<void> host_data;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> version;
   Function<Pointer<const void> ,Pointer<const struct wclap_host> host, Pointer<const char> extension_id> get_extension;
   Function<void,Pointer<const struct wclap_host> host> request_restart;
   Function<void,Pointer<const struct wclap_host> host> request_process;
   Function<void,Pointer<const struct wclap_host> host> request_callback;
};
typedef uint32_t wclap_id;
struct wclap_version {
   uint32_t major;
   uint32_t minor;
   uint32_t revision;
};
struct wclap_host {
   wclap_version_t wclap_version;

   Pointer<void> host_data;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> version;
   Function<Pointer<const void> ,Pointer<const struct wclap_host> host, Pointer<const char> extension_id> get_extension;
   Function<void,Pointer<const struct wclap_host> host> request_restart;
   Function<void,Pointer<const struct wclap_host> host> request_process;
   Function<void,Pointer<const struct wclap_host> host> request_callback;
};
typedef int64_t wclap_beattime;
typedef int64_t wclap_sectime;
typedef uint32_t wclap_id;
typedef int32_t wclap_note_expression;
struct wclap_event_header {
   uint32_t size;
   uint32_t time;
   uint16_t space_id;
   uint16_t type;
   uint32_t flags;
};
struct wclap_event_note {
   wclap_event_header_t header;

   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;
   double  velocity;
};
struct wclap_event_note_expression {
   wclap_event_header_t header;

   wclap_note_expression expression_id;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_value {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_mod {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double amount;
};
struct wclap_event_param_gesture {
   wclap_event_header_t header;
   wclap_id param_id;
};
struct wclap_event_transport {
   wclap_event_header_t header;

   uint32_t flags;

   wclap_beattime song_pos_beats;
   wclap_sectime  song_pos_seconds;

   double tempo;
   double tempo_inc;

   wclap_beattime loop_start_beats;
   wclap_beattime loop_end_beats;
   wclap_sectime  loop_start_seconds;
   wclap_sectime  loop_end_seconds;

   wclap_beattime bar_start;
   int32_t       bar_number;

   uint16_t tsig_num;
   uint16_t tsig_denom;
};
struct wclap_event_midi {
   wclap_event_header_t header;

   uint16_t port_index;
   uint8_t  data[3];
};
struct wclap_event_midi_sysex {
   wclap_event_header_t header;

   uint16_t       port_index;
   Pointer<const uint8_t> buffer;
   uint32_t       size;
};
struct wclap_event_midi2 {
   wclap_event_header_t header;

   uint16_t port_index;
   uint32_t data[4];
};
struct wclap_input_events {
   Pointer<void> ctx;
   Function<uint32_t,Pointer<const struct wclap_input_events> list> size;
   Function<Pointer<const wclap_event_header_t> ,Pointer<const struct wclap_input_events> list, uint32_t index> get;
};
struct wclap_output_events {
   Pointer<void> ctx;
   Function<bool,Pointer<const struct wclap_output_events> list,
                            Pointer<const wclap_event_header_t>       event> try_push;
};
struct wclap_audio_buffer {
   Pointer<Pointer<float>>  data32;
   Pointer<Pointer<double>> data64;
   uint32_t channel_count;
   uint32_t latency;
   uint64_t constant_mask;
};
typedef int32_t wclap_process_status;
struct wclap_process {
   int64_t steady_time;
   uint32_t frames_count;
   Pointer<const wclap_event_transport_t> transport;
   Pointer<const wclap_audio_buffer_t> audio_inputs;
   Pointer<wclap_audio_buffer_t>       audio_outputs;
   uint32_t                   audio_inputs_count;
   uint32_t                   audio_outputs_count;
   Pointer<const wclap_input_events_t>  in_events;
   Pointer<const wclap_output_events_t> out_events;
};
struct wclap_plugin_descriptor {
   wclap_version_t wclap_version;
   Pointer<const char> id;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> manual_url;
   Pointer<const char> support_url;
   Pointer<const char> version;
   Pointer<const char> description;
   Pointer<const char> Pointer<const> features;
};
struct wclap_plugin {
   Pointer<const wclap_plugin_descriptor_t> desc;

   Pointer<void> plugin_data;
   Function<bool,Pointer<const struct wclap_plugin> plugin> init;
   Function<void,Pointer<const struct wclap_plugin> plugin> destroy;
   Function<bool,Pointer<const struct wclap_plugin> plugin,
                            double                    sample_rate,
                            uint32_t                  min_frames_count,
                            uint32_t                  max_frames_count> activate;
   Function<void,Pointer<const struct wclap_plugin> plugin> deactivate;
   Function<bool,Pointer<const struct wclap_plugin> plugin> start_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> stop_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> reset;
   Function<wclap_process_status,Pointer<const struct wclap_plugin> plugin,
                                          Pointer<const wclap_process_t>     process> process;
   Function<Pointer<const void> ,Pointer<const struct wclap_plugin> plugin, Pointer<const char> id> get_extension;
   Function<void,Pointer<const struct wclap_plugin> plugin> on_main_thread;
};
typedef int64_t wclap_beattime;
typedef int64_t wclap_sectime;
typedef uint32_t wclap_id;
typedef int32_t wclap_note_expression;
struct wclap_event_header {
   uint32_t size;
   uint32_t time;
   uint16_t space_id;
   uint16_t type;
   uint32_t flags;
};
struct wclap_event_note {
   wclap_event_header_t header;

   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;
   double  velocity;
};
struct wclap_event_note_expression {
   wclap_event_header_t header;

   wclap_note_expression expression_id;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_value {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_mod {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double amount;
};
struct wclap_event_param_gesture {
   wclap_event_header_t header;
   wclap_id param_id;
};
struct wclap_event_transport {
   wclap_event_header_t header;

   uint32_t flags;

   wclap_beattime song_pos_beats;
   wclap_sectime  song_pos_seconds;

   double tempo;
   double tempo_inc;

   wclap_beattime loop_start_beats;
   wclap_beattime loop_end_beats;
   wclap_sectime  loop_start_seconds;
   wclap_sectime  loop_end_seconds;

   wclap_beattime bar_start;
   int32_t       bar_number;

   uint16_t tsig_num;
   uint16_t tsig_denom;
};
struct wclap_event_midi {
   wclap_event_header_t header;

   uint16_t port_index;
   uint8_t  data[3];
};
struct wclap_event_midi_sysex {
   wclap_event_header_t header;

   uint16_t       port_index;
   Pointer<const uint8_t> buffer;
   uint32_t       size;
};
struct wclap_event_midi2 {
   wclap_event_header_t header;

   uint16_t port_index;
   uint32_t data[4];
};
struct wclap_input_events {
   Pointer<void> ctx;
   Function<uint32_t,Pointer<const struct wclap_input_events> list> size;
   Function<Pointer<const wclap_event_header_t> ,Pointer<const struct wclap_input_events> list, uint32_t index> get;
};
struct wclap_output_events {
   Pointer<void> ctx;
   Function<bool,Pointer<const struct wclap_output_events> list,
                            Pointer<const wclap_event_header_t>       event> try_push;
};
struct wclap_audio_buffer {
   Pointer<Pointer<float>>  data32;
   Pointer<Pointer<double>> data64;
   uint32_t channel_count;
   uint32_t latency;
   uint64_t constant_mask;
};
typedef int32_t wclap_process_status;
struct wclap_process {
   int64_t steady_time;
   uint32_t frames_count;
   Pointer<const wclap_event_transport_t> transport;
   Pointer<const wclap_audio_buffer_t> audio_inputs;
   Pointer<wclap_audio_buffer_t>       audio_outputs;
   uint32_t                   audio_inputs_count;
   uint32_t                   audio_outputs_count;
   Pointer<const wclap_input_events_t>  in_events;
   Pointer<const wclap_output_events_t> out_events;
};
struct wclap_istream {
   Pointer<void> ctx;
   Function<int64_t,Pointer<const struct wclap_istream> stream, Pointer<void> buffer, uint64_t size> read;
};
struct wclap_ostream {
   Pointer<void> ctx;
   Function<int64_t,Pointer<const struct wclap_ostream> stream, Pointer<const void> buffer, uint64_t size> write;
};
typedef uint64_t wclap_timestamp;
struct wclap_universal_plugin_id {
   Pointer<const char> abi;
   Pointer<const char> id;
};
struct wclap_version {
   uint32_t major;
   uint32_t minor;
   uint32_t revision;
};
struct wclap_version {
   uint32_t major;
   uint32_t minor;
   uint32_t revision;
};
struct wclap_host {
   wclap_version_t wclap_version;

   Pointer<void> host_data;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> version;
   Function<Pointer<const void> ,Pointer<const struct wclap_host> host, Pointer<const char> extension_id> get_extension;
   Function<void,Pointer<const struct wclap_host> host> request_restart;
   Function<void,Pointer<const struct wclap_host> host> request_process;
   Function<void,Pointer<const struct wclap_host> host> request_callback;
};
typedef int64_t wclap_beattime;
typedef int64_t wclap_sectime;
typedef uint32_t wclap_id;
typedef int32_t wclap_note_expression;
struct wclap_event_header {
   uint32_t size;
   uint32_t time;
   uint16_t space_id;
   uint16_t type;
   uint32_t flags;
};
struct wclap_event_note {
   wclap_event_header_t header;

   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;
   double  velocity;
};
struct wclap_event_note_expression {
   wclap_event_header_t header;

   wclap_note_expression expression_id;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_value {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_mod {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double amount;
};
struct wclap_event_param_gesture {
   wclap_event_header_t header;
   wclap_id param_id;
};
struct wclap_event_transport {
   wclap_event_header_t header;

   uint32_t flags;

   wclap_beattime song_pos_beats;
   wclap_sectime  song_pos_seconds;

   double tempo;
   double tempo_inc;

   wclap_beattime loop_start_beats;
   wclap_beattime loop_end_beats;
   wclap_sectime  loop_start_seconds;
   wclap_sectime  loop_end_seconds;

   wclap_beattime bar_start;
   int32_t       bar_number;

   uint16_t tsig_num;
   uint16_t tsig_denom;
};
struct wclap_event_midi {
   wclap_event_header_t header;

   uint16_t port_index;
   uint8_t  data[3];
};
struct wclap_event_midi_sysex {
   wclap_event_header_t header;

   uint16_t       port_index;
   Pointer<const uint8_t> buffer;
   uint32_t       size;
};
struct wclap_event_midi2 {
   wclap_event_header_t header;

   uint16_t port_index;
   uint32_t data[4];
};
struct wclap_input_events {
   Pointer<void> ctx;
   Function<uint32_t,Pointer<const struct wclap_input_events> list> size;
   Function<Pointer<const wclap_event_header_t> ,Pointer<const struct wclap_input_events> list, uint32_t index> get;
};
struct wclap_output_events {
   Pointer<void> ctx;
   Function<bool,Pointer<const struct wclap_output_events> list,
                            Pointer<const wclap_event_header_t>       event> try_push;
};
struct wclap_audio_buffer {
   Pointer<Pointer<float>>  data32;
   Pointer<Pointer<double>> data64;
   uint32_t channel_count;
   uint32_t latency;
   uint64_t constant_mask;
};
typedef int32_t wclap_process_status;
struct wclap_process {
   int64_t steady_time;
   uint32_t frames_count;
   Pointer<const wclap_event_transport_t> transport;
   Pointer<const wclap_audio_buffer_t> audio_inputs;
   Pointer<wclap_audio_buffer_t>       audio_outputs;
   uint32_t                   audio_inputs_count;
   uint32_t                   audio_outputs_count;
   Pointer<const wclap_input_events_t>  in_events;
   Pointer<const wclap_output_events_t> out_events;
};
struct wclap_plugin_descriptor {
   wclap_version_t wclap_version;
   Pointer<const char> id;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> manual_url;
   Pointer<const char> support_url;
   Pointer<const char> version;
   Pointer<const char> description;
   Pointer<const char> Pointer<const> features;
};
struct wclap_plugin {
   Pointer<const wclap_plugin_descriptor_t> desc;

   Pointer<void> plugin_data;
   Function<bool,Pointer<const struct wclap_plugin> plugin> init;
   Function<void,Pointer<const struct wclap_plugin> plugin> destroy;
   Function<bool,Pointer<const struct wclap_plugin> plugin,
                            double                    sample_rate,
                            uint32_t                  min_frames_count,
                            uint32_t                  max_frames_count> activate;
   Function<void,Pointer<const struct wclap_plugin> plugin> deactivate;
   Function<bool,Pointer<const struct wclap_plugin> plugin> start_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> stop_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> reset;
   Function<wclap_process_status,Pointer<const struct wclap_plugin> plugin,
                                          Pointer<const wclap_process_t>     process> process;
   Function<Pointer<const void> ,Pointer<const struct wclap_plugin> plugin, Pointer<const char> id> get_extension;
   Function<void,Pointer<const struct wclap_plugin> plugin> on_main_thread;
};
struct wclap_plugin_factory {
   Function<uint32_t,Pointer<const struct wclap_plugin_factory> factory> get_plugin_count;
   Function<Pointer<const wclap_plugin_descriptor_t> ,
      Pointer<const struct wclap_plugin_factory> factory, uint32_t index> get_plugin_descriptor;
   Function<Pointer<const wclap_plugin_t> ,Pointer<const struct wclap_plugin_factory> factory,
                                                  Pointer<const wclap_host_t>                host,
                                                  Pointer<const char>                       plugin_id> create_plugin;
};
typedef uint64_t wclap_timestamp;
struct wclap_version {
   uint32_t major;
   uint32_t minor;
   uint32_t revision;
};
struct wclap_universal_plugin_id {
   Pointer<const char> abi;
   Pointer<const char> id;
};
struct wclap_preset_discovery_metadata_receiver {
   Pointer<void> receiver_data;
   Function<void,Pointer<const struct wclap_preset_discovery_metadata_receiver> receiver,
                            int32_t                                               os_error,
                            Pointer<const char>                                           error_message> on_error;
   Function<bool,Pointer<const struct wclap_preset_discovery_metadata_receiver> receiver,
                                Pointer<const char>                                           name,
                                Pointer<const char>                                           load_key> begin_preset;
   Function<void,Pointer<const struct wclap_preset_discovery_metadata_receiver> receiver,
                                 Pointer<const wclap_universal_plugin_id_t>                     plugin_id> add_plugin_id;
   Function<void,Pointer<const struct wclap_preset_discovery_metadata_receiver> receiver,
                                    Pointer<const char> soundpack_id> set_soundpack_id;
   Function<void,Pointer<const struct wclap_preset_discovery_metadata_receiver> receiver,
                             uint32_t                                              flags> set_flags;
   Function<void,Pointer<const struct wclap_preset_discovery_metadata_receiver> receiver,
                               Pointer<const char>                                           creator> add_creator;
   Function<void,Pointer<const struct wclap_preset_discovery_metadata_receiver> receiver,
                                   Pointer<const char> description> set_description;
   Function<void,Pointer<const struct wclap_preset_discovery_metadata_receiver> receiver,
                                  wclap_timestamp creation_time,
                                  wclap_timestamp modification_time> set_timestamps;
   Function<void,Pointer<const struct wclap_preset_discovery_metadata_receiver> receiver,
                               Pointer<const char>                                           feature> add_feature;
   Function<void,Pointer<const struct wclap_preset_discovery_metadata_receiver> receiver,
                                  Pointer<const char>                                           key,
                                  Pointer<const char>                                           value> add_extra_info;
};
struct wclap_preset_discovery_filetype {
   Pointer<const char> name;
   Pointer<const char> description;
   Pointer<const char> file_extension;
};
struct wclap_preset_discovery_location {
   uint32_t    flags;
   Pointer<const char> name;
   uint32_t    kind;
   Pointer<const char> location;
};
struct wclap_preset_discovery_soundpack {
   uint32_t       flags;
   Pointer<const char>    id;
   Pointer<const char>    name;
   Pointer<const char>    description;
   Pointer<const char>    homepage_url;
   Pointer<const char>    vendor;
   Pointer<const char>    image_path;
   wclap_timestamp release_timestamp;
};
struct wclap_preset_discovery_provider_descriptor {
   wclap_version_t wclap_version;
   Pointer<const char>    id;
   Pointer<const char>    name;
   Pointer<const char>    vendor;
};
struct wclap_preset_discovery_provider {
   Pointer<const wclap_preset_discovery_provider_descriptor_t> desc;

   Pointer<void> provider_data;
   Function<bool,Pointer<const struct wclap_preset_discovery_provider> provider> init;
   Function<void,Pointer<const struct wclap_preset_discovery_provider> provider> destroy;
   Function<bool,Pointer<const struct wclap_preset_discovery_provider>     provider,
                                uint32_t                                         location_kind,
                                Pointer<const char>                                      location,
                                Pointer<const wclap_preset_discovery_metadata_receiver_t> metadata_receiver> get_metadata;
   Function<Pointer<const void> ,Pointer<const struct wclap_preset_discovery_provider> provider,
                                         Pointer<const char>                                  extension_id> get_extension;
};
struct wclap_preset_discovery_indexer {
   wclap_version_t wclap_version;
   Pointer<const char>    name;
   Pointer<const char>    vendor;
   Pointer<const char>    url;
   Pointer<const char> version;

   Pointer<void> indexer_data;
   Function<bool,Pointer<const struct wclap_preset_discovery_indexer> indexer,
                                    Pointer<const wclap_preset_discovery_filetype_t>     filetype> declare_filetype;
   Function<bool,Pointer<const struct wclap_preset_discovery_indexer> indexer,
                                    Pointer<const wclap_preset_discovery_location_t>     location> declare_location;
   Function<bool,Pointer<const struct wclap_preset_discovery_indexer> indexer,
                                     Pointer<const wclap_preset_discovery_soundpack_t>    soundpack> declare_soundpack;
   Function<Pointer<const void> ,Pointer<const struct wclap_preset_discovery_indexer> indexer,
                                         Pointer<const char>                                 extension_id> get_extension;
};
struct wclap_preset_discovery_factory {
   Function<uint32_t,Pointer<const struct wclap_preset_discovery_factory> factory> count;
   Function<Pointer<const wclap_preset_discovery_provider_descriptor_t> ,
      Pointer<const struct wclap_preset_discovery_factory> factory, uint32_t index> get_descriptor;
   Function<Pointer<const wclap_preset_discovery_provider_t> ,
      Pointer<const struct wclap_preset_discovery_factory> factory,
      Pointer<const wclap_preset_discovery_indexer_t>      indexer,
      Pointer<const char>                                 provider_id> create;
};
struct wclap_plugin_invalidation_source {
   Pointer<const char> directory;
   Pointer<const char> filename_glob;
   bool recursive_scan;
};
struct wclap_plugin_invalidation_factory {
   Function<uint32_t,Pointer<const struct wclap_plugin_invalidation_factory> factory> count;
   Function<Pointer<const wclap_plugin_invalidation_source_t> ,
      Pointer<const struct wclap_plugin_invalidation_factory> factory, uint32_t index> get;
   Function<bool,Pointer<const struct wclap_plugin_invalidation_factory> factory> refresh;
};
typedef uint32_t wclap_id;
struct wclap_universal_plugin_id {
   Pointer<const char> abi;
   Pointer<const char> id;
};
struct wclap_istream {
   Pointer<void> ctx;
   Function<int64_t,Pointer<const struct wclap_istream> stream, Pointer<void> buffer, uint64_t size> read;
};
struct wclap_ostream {
   Pointer<void> ctx;
   Function<int64_t,Pointer<const struct wclap_ostream> stream, Pointer<const void> buffer, uint64_t size> write;
};
struct wclap_version {
   uint32_t major;
   uint32_t minor;
   uint32_t revision;
};
struct wclap_plugin_state_converter_descriptor {
   wclap_version_t wclap_version;

   wclap_universal_plugin_id_t src_plugin_id;
   wclap_universal_plugin_id_t dst_plugin_id;

   Pointer<const char> id;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> version;
   Pointer<const char> description;
};
struct wclap_plugin_state_converter {
   Pointer<const wclap_plugin_state_converter_descriptor_t> desc;

   Pointer<void> converter_data;
   Function<void ,Pointer<struct wclap_plugin_state_converter> converter> destroy;
   Function<bool ,Pointer<struct wclap_plugin_state_converter> converter,
                         Pointer<const wclap_istream_t>               src,
                         Pointer<const wclap_ostream_t>               dst,
                         Pointer<char>                               error_buffer,
                         size_t                              error_buffer_size> convert_state;
   Function<bool ,Pointer<struct wclap_plugin_state_converter> converter,
                                    wclap_id                             src_param_id,
                                    double                              src_normalized_value,
                                    Pointer<wclap_id>                            dst_param_id,
                                    Pointer<double>                             dst_normalized_value> convert_normalized_value;
   Function<bool ,Pointer<struct wclap_plugin_state_converter> converter,
                               wclap_id                             src_param_id,
                               double                              src_plain_value,
                               Pointer<wclap_id>                            dst_param_id,
                               Pointer<double>                             dst_plain_value> convert_plain_value;
};
struct wclap_plugin_state_converter_factory {
   Function<uint32_t ,Pointer<const struct wclap_plugin_state_converter_factory> factory> count;
   Function<Pointer<const wclap_plugin_state_converter_descriptor_t> ,
      Pointer<const struct wclap_plugin_state_converter_factory> factory, uint32_t index> get_descriptor;
   Function<Pointer<wclap_plugin_state_converter_t> ,
      Pointer<const struct wclap_plugin_state_converter_factory> factory, Pointer<const char> converter_id> create;
};
struct wclap_version {
   uint32_t major;
   uint32_t minor;
   uint32_t revision;
};
struct wclap_host {
   wclap_version_t wclap_version;

   Pointer<void> host_data;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> version;
   Function<Pointer<const void> ,Pointer<const struct wclap_host> host, Pointer<const char> extension_id> get_extension;
   Function<void,Pointer<const struct wclap_host> host> request_restart;
   Function<void,Pointer<const struct wclap_host> host> request_process;
   Function<void,Pointer<const struct wclap_host> host> request_callback;
};
typedef int64_t wclap_beattime;
typedef int64_t wclap_sectime;
typedef uint32_t wclap_id;
typedef int32_t wclap_note_expression;
struct wclap_event_header {
   uint32_t size;
   uint32_t time;
   uint16_t space_id;
   uint16_t type;
   uint32_t flags;
};
struct wclap_event_note {
   wclap_event_header_t header;

   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;
   double  velocity;
};
struct wclap_event_note_expression {
   wclap_event_header_t header;

   wclap_note_expression expression_id;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_value {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_mod {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double amount;
};
struct wclap_event_param_gesture {
   wclap_event_header_t header;
   wclap_id param_id;
};
struct wclap_event_transport {
   wclap_event_header_t header;

   uint32_t flags;

   wclap_beattime song_pos_beats;
   wclap_sectime  song_pos_seconds;

   double tempo;
   double tempo_inc;

   wclap_beattime loop_start_beats;
   wclap_beattime loop_end_beats;
   wclap_sectime  loop_start_seconds;
   wclap_sectime  loop_end_seconds;

   wclap_beattime bar_start;
   int32_t       bar_number;

   uint16_t tsig_num;
   uint16_t tsig_denom;
};
struct wclap_event_midi {
   wclap_event_header_t header;

   uint16_t port_index;
   uint8_t  data[3];
};
struct wclap_event_midi_sysex {
   wclap_event_header_t header;

   uint16_t       port_index;
   Pointer<const uint8_t> buffer;
   uint32_t       size;
};
struct wclap_event_midi2 {
   wclap_event_header_t header;

   uint16_t port_index;
   uint32_t data[4];
};
struct wclap_input_events {
   Pointer<void> ctx;
   Function<uint32_t,Pointer<const struct wclap_input_events> list> size;
   Function<Pointer<const wclap_event_header_t> ,Pointer<const struct wclap_input_events> list, uint32_t index> get;
};
struct wclap_output_events {
   Pointer<void> ctx;
   Function<bool,Pointer<const struct wclap_output_events> list,
                            Pointer<const wclap_event_header_t>       event> try_push;
};
struct wclap_audio_buffer {
   Pointer<Pointer<float>>  data32;
   Pointer<Pointer<double>> data64;
   uint32_t channel_count;
   uint32_t latency;
   uint64_t constant_mask;
};
typedef int32_t wclap_process_status;
struct wclap_process {
   int64_t steady_time;
   uint32_t frames_count;
   Pointer<const wclap_event_transport_t> transport;
   Pointer<const wclap_audio_buffer_t> audio_inputs;
   Pointer<wclap_audio_buffer_t>       audio_outputs;
   uint32_t                   audio_inputs_count;
   uint32_t                   audio_outputs_count;
   Pointer<const wclap_input_events_t>  in_events;
   Pointer<const wclap_output_events_t> out_events;
};
struct wclap_plugin_descriptor {
   wclap_version_t wclap_version;
   Pointer<const char> id;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> manual_url;
   Pointer<const char> support_url;
   Pointer<const char> version;
   Pointer<const char> description;
   Pointer<const char> Pointer<const> features;
};
struct wclap_plugin {
   Pointer<const wclap_plugin_descriptor_t> desc;

   Pointer<void> plugin_data;
   Function<bool,Pointer<const struct wclap_plugin> plugin> init;
   Function<void,Pointer<const struct wclap_plugin> plugin> destroy;
   Function<bool,Pointer<const struct wclap_plugin> plugin,
                            double                    sample_rate,
                            uint32_t                  min_frames_count,
                            uint32_t                  max_frames_count> activate;
   Function<void,Pointer<const struct wclap_plugin> plugin> deactivate;
   Function<bool,Pointer<const struct wclap_plugin> plugin> start_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> stop_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> reset;
   Function<wclap_process_status,Pointer<const struct wclap_plugin> plugin,
                                          Pointer<const wclap_process_t>     process> process;
   Function<Pointer<const void> ,Pointer<const struct wclap_plugin> plugin, Pointer<const char> id> get_extension;
   Function<void,Pointer<const struct wclap_plugin> plugin> on_main_thread;
};
struct wclap_ambisonic_config {
   uint32_t ordering;
   uint32_t normalization;
};
struct wclap_plugin_ambisonic {
   Function<bool,Pointer<const wclap_plugin_t>           plugin,
                                       Pointer<const wclap_ambisonic_config_t> config> is_config_supported;
   Function<bool,Pointer<const wclap_plugin_t>     plugin,
                              bool                     is_input,
                              uint32_t                 port_index,
                              Pointer<wclap_ambisonic_config_t> config> get_config;

};
struct wclap_host_ambisonic {
   Function<void,Pointer<const wclap_host_t> host> changed;
};
struct wclap_version {
   uint32_t major;
   uint32_t minor;
   uint32_t revision;
};
struct wclap_host {
   wclap_version_t wclap_version;

   Pointer<void> host_data;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> version;
   Function<Pointer<const void> ,Pointer<const struct wclap_host> host, Pointer<const char> extension_id> get_extension;
   Function<void,Pointer<const struct wclap_host> host> request_restart;
   Function<void,Pointer<const struct wclap_host> host> request_process;
   Function<void,Pointer<const struct wclap_host> host> request_callback;
};
typedef int64_t wclap_beattime;
typedef int64_t wclap_sectime;
typedef uint32_t wclap_id;
typedef int32_t wclap_note_expression;
struct wclap_event_header {
   uint32_t size;
   uint32_t time;
   uint16_t space_id;
   uint16_t type;
   uint32_t flags;
};
struct wclap_event_note {
   wclap_event_header_t header;

   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;
   double  velocity;
};
struct wclap_event_note_expression {
   wclap_event_header_t header;

   wclap_note_expression expression_id;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_value {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_mod {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double amount;
};
struct wclap_event_param_gesture {
   wclap_event_header_t header;
   wclap_id param_id;
};
struct wclap_event_transport {
   wclap_event_header_t header;

   uint32_t flags;

   wclap_beattime song_pos_beats;
   wclap_sectime  song_pos_seconds;

   double tempo;
   double tempo_inc;

   wclap_beattime loop_start_beats;
   wclap_beattime loop_end_beats;
   wclap_sectime  loop_start_seconds;
   wclap_sectime  loop_end_seconds;

   wclap_beattime bar_start;
   int32_t       bar_number;

   uint16_t tsig_num;
   uint16_t tsig_denom;
};
struct wclap_event_midi {
   wclap_event_header_t header;

   uint16_t port_index;
   uint8_t  data[3];
};
struct wclap_event_midi_sysex {
   wclap_event_header_t header;

   uint16_t       port_index;
   Pointer<const uint8_t> buffer;
   uint32_t       size;
};
struct wclap_event_midi2 {
   wclap_event_header_t header;

   uint16_t port_index;
   uint32_t data[4];
};
struct wclap_input_events {
   Pointer<void> ctx;
   Function<uint32_t,Pointer<const struct wclap_input_events> list> size;
   Function<Pointer<const wclap_event_header_t> ,Pointer<const struct wclap_input_events> list, uint32_t index> get;
};
struct wclap_output_events {
   Pointer<void> ctx;
   Function<bool,Pointer<const struct wclap_output_events> list,
                            Pointer<const wclap_event_header_t>       event> try_push;
};
struct wclap_audio_buffer {
   Pointer<Pointer<float>>  data32;
   Pointer<Pointer<double>> data64;
   uint32_t channel_count;
   uint32_t latency;
   uint64_t constant_mask;
};
typedef int32_t wclap_process_status;
struct wclap_process {
   int64_t steady_time;
   uint32_t frames_count;
   Pointer<const wclap_event_transport_t> transport;
   Pointer<const wclap_audio_buffer_t> audio_inputs;
   Pointer<wclap_audio_buffer_t>       audio_outputs;
   uint32_t                   audio_inputs_count;
   uint32_t                   audio_outputs_count;
   Pointer<const wclap_input_events_t>  in_events;
   Pointer<const wclap_output_events_t> out_events;
};
struct wclap_plugin_descriptor {
   wclap_version_t wclap_version;
   Pointer<const char> id;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> manual_url;
   Pointer<const char> support_url;
   Pointer<const char> version;
   Pointer<const char> description;
   Pointer<const char> Pointer<const> features;
};
struct wclap_plugin {
   Pointer<const wclap_plugin_descriptor_t> desc;

   Pointer<void> plugin_data;
   Function<bool,Pointer<const struct wclap_plugin> plugin> init;
   Function<void,Pointer<const struct wclap_plugin> plugin> destroy;
   Function<bool,Pointer<const struct wclap_plugin> plugin,
                            double                    sample_rate,
                            uint32_t                  min_frames_count,
                            uint32_t                  max_frames_count> activate;
   Function<void,Pointer<const struct wclap_plugin> plugin> deactivate;
   Function<bool,Pointer<const struct wclap_plugin> plugin> start_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> stop_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> reset;
   Function<wclap_process_status,Pointer<const struct wclap_plugin> plugin,
                                          Pointer<const wclap_process_t>     process> process;
   Function<Pointer<const void> ,Pointer<const struct wclap_plugin> plugin, Pointer<const char> id> get_extension;
   Function<void,Pointer<const struct wclap_plugin> plugin> on_main_thread;
};
struct wclap_plugin_audio_ports_activation {
   Function<bool,Pointer<const wclap_plugin_t> plugin> can_activate_while_processing;
   Function<bool,Pointer<const wclap_plugin_t> plugin,
                              bool                 is_input,
                              uint32_t             port_index,
                              bool                 is_active,
                              uint32_t             sample_size> set_active;
};
struct wclap_version {
   uint32_t major;
   uint32_t minor;
   uint32_t revision;
};
struct wclap_host {
   wclap_version_t wclap_version;

   Pointer<void> host_data;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> version;
   Function<Pointer<const void> ,Pointer<const struct wclap_host> host, Pointer<const char> extension_id> get_extension;
   Function<void,Pointer<const struct wclap_host> host> request_restart;
   Function<void,Pointer<const struct wclap_host> host> request_process;
   Function<void,Pointer<const struct wclap_host> host> request_callback;
};
typedef int64_t wclap_beattime;
typedef int64_t wclap_sectime;
typedef uint32_t wclap_id;
typedef int32_t wclap_note_expression;
struct wclap_event_header {
   uint32_t size;
   uint32_t time;
   uint16_t space_id;
   uint16_t type;
   uint32_t flags;
};
struct wclap_event_note {
   wclap_event_header_t header;

   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;
   double  velocity;
};
struct wclap_event_note_expression {
   wclap_event_header_t header;

   wclap_note_expression expression_id;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_value {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_mod {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double amount;
};
struct wclap_event_param_gesture {
   wclap_event_header_t header;
   wclap_id param_id;
};
struct wclap_event_transport {
   wclap_event_header_t header;

   uint32_t flags;

   wclap_beattime song_pos_beats;
   wclap_sectime  song_pos_seconds;

   double tempo;
   double tempo_inc;

   wclap_beattime loop_start_beats;
   wclap_beattime loop_end_beats;
   wclap_sectime  loop_start_seconds;
   wclap_sectime  loop_end_seconds;

   wclap_beattime bar_start;
   int32_t       bar_number;

   uint16_t tsig_num;
   uint16_t tsig_denom;
};
struct wclap_event_midi {
   wclap_event_header_t header;

   uint16_t port_index;
   uint8_t  data[3];
};
struct wclap_event_midi_sysex {
   wclap_event_header_t header;

   uint16_t       port_index;
   Pointer<const uint8_t> buffer;
   uint32_t       size;
};
struct wclap_event_midi2 {
   wclap_event_header_t header;

   uint16_t port_index;
   uint32_t data[4];
};
struct wclap_input_events {
   Pointer<void> ctx;
   Function<uint32_t,Pointer<const struct wclap_input_events> list> size;
   Function<Pointer<const wclap_event_header_t> ,Pointer<const struct wclap_input_events> list, uint32_t index> get;
};
struct wclap_output_events {
   Pointer<void> ctx;
   Function<bool,Pointer<const struct wclap_output_events> list,
                            Pointer<const wclap_event_header_t>       event> try_push;
};
struct wclap_audio_buffer {
   Pointer<Pointer<float>>  data32;
   Pointer<Pointer<double>> data64;
   uint32_t channel_count;
   uint32_t latency;
   uint64_t constant_mask;
};
typedef int32_t wclap_process_status;
struct wclap_process {
   int64_t steady_time;
   uint32_t frames_count;
   Pointer<const wclap_event_transport_t> transport;
   Pointer<const wclap_audio_buffer_t> audio_inputs;
   Pointer<wclap_audio_buffer_t>       audio_outputs;
   uint32_t                   audio_inputs_count;
   uint32_t                   audio_outputs_count;
   Pointer<const wclap_input_events_t>  in_events;
   Pointer<const wclap_output_events_t> out_events;
};
struct wclap_plugin_descriptor {
   wclap_version_t wclap_version;
   Pointer<const char> id;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> manual_url;
   Pointer<const char> support_url;
   Pointer<const char> version;
   Pointer<const char> description;
   Pointer<const char> Pointer<const> features;
};
struct wclap_plugin {
   Pointer<const wclap_plugin_descriptor_t> desc;

   Pointer<void> plugin_data;
   Function<bool,Pointer<const struct wclap_plugin> plugin> init;
   Function<void,Pointer<const struct wclap_plugin> plugin> destroy;
   Function<bool,Pointer<const struct wclap_plugin> plugin,
                            double                    sample_rate,
                            uint32_t                  min_frames_count,
                            uint32_t                  max_frames_count> activate;
   Function<void,Pointer<const struct wclap_plugin> plugin> deactivate;
   Function<bool,Pointer<const struct wclap_plugin> plugin> start_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> stop_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> reset;
   Function<wclap_process_status,Pointer<const struct wclap_plugin> plugin,
                                          Pointer<const wclap_process_t>     process> process;
   Function<Pointer<const void> ,Pointer<const struct wclap_plugin> plugin, Pointer<const char> id> get_extension;
   Function<void,Pointer<const struct wclap_plugin> plugin> on_main_thread;
};
struct wclap_version {
   uint32_t major;
   uint32_t minor;
   uint32_t revision;
};
struct wclap_host {
   wclap_version_t wclap_version;

   Pointer<void> host_data;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> version;
   Function<Pointer<const void> ,Pointer<const struct wclap_host> host, Pointer<const char> extension_id> get_extension;
   Function<void,Pointer<const struct wclap_host> host> request_restart;
   Function<void,Pointer<const struct wclap_host> host> request_process;
   Function<void,Pointer<const struct wclap_host> host> request_callback;
};
typedef int64_t wclap_beattime;
typedef int64_t wclap_sectime;
typedef uint32_t wclap_id;
typedef int32_t wclap_note_expression;
struct wclap_event_header {
   uint32_t size;
   uint32_t time;
   uint16_t space_id;
   uint16_t type;
   uint32_t flags;
};
struct wclap_event_note {
   wclap_event_header_t header;

   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;
   double  velocity;
};
struct wclap_event_note_expression {
   wclap_event_header_t header;

   wclap_note_expression expression_id;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_value {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_mod {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double amount;
};
struct wclap_event_param_gesture {
   wclap_event_header_t header;
   wclap_id param_id;
};
struct wclap_event_transport {
   wclap_event_header_t header;

   uint32_t flags;

   wclap_beattime song_pos_beats;
   wclap_sectime  song_pos_seconds;

   double tempo;
   double tempo_inc;

   wclap_beattime loop_start_beats;
   wclap_beattime loop_end_beats;
   wclap_sectime  loop_start_seconds;
   wclap_sectime  loop_end_seconds;

   wclap_beattime bar_start;
   int32_t       bar_number;

   uint16_t tsig_num;
   uint16_t tsig_denom;
};
struct wclap_event_midi {
   wclap_event_header_t header;

   uint16_t port_index;
   uint8_t  data[3];
};
struct wclap_event_midi_sysex {
   wclap_event_header_t header;

   uint16_t       port_index;
   Pointer<const uint8_t> buffer;
   uint32_t       size;
};
struct wclap_event_midi2 {
   wclap_event_header_t header;

   uint16_t port_index;
   uint32_t data[4];
};
struct wclap_input_events {
   Pointer<void> ctx;
   Function<uint32_t,Pointer<const struct wclap_input_events> list> size;
   Function<Pointer<const wclap_event_header_t> ,Pointer<const struct wclap_input_events> list, uint32_t index> get;
};
struct wclap_output_events {
   Pointer<void> ctx;
   Function<bool,Pointer<const struct wclap_output_events> list,
                            Pointer<const wclap_event_header_t>       event> try_push;
};
struct wclap_audio_buffer {
   Pointer<Pointer<float>>  data32;
   Pointer<Pointer<double>> data64;
   uint32_t channel_count;
   uint32_t latency;
   uint64_t constant_mask;
};
typedef int32_t wclap_process_status;
struct wclap_process {
   int64_t steady_time;
   uint32_t frames_count;
   Pointer<const wclap_event_transport_t> transport;
   Pointer<const wclap_audio_buffer_t> audio_inputs;
   Pointer<wclap_audio_buffer_t>       audio_outputs;
   uint32_t                   audio_inputs_count;
   uint32_t                   audio_outputs_count;
   Pointer<const wclap_input_events_t>  in_events;
   Pointer<const wclap_output_events_t> out_events;
};
struct wclap_plugin_descriptor {
   wclap_version_t wclap_version;
   Pointer<const char> id;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> manual_url;
   Pointer<const char> support_url;
   Pointer<const char> version;
   Pointer<const char> description;
   Pointer<const char> Pointer<const> features;
};
struct wclap_plugin {
   Pointer<const wclap_plugin_descriptor_t> desc;

   Pointer<void> plugin_data;
   Function<bool,Pointer<const struct wclap_plugin> plugin> init;
   Function<void,Pointer<const struct wclap_plugin> plugin> destroy;
   Function<bool,Pointer<const struct wclap_plugin> plugin,
                            double                    sample_rate,
                            uint32_t                  min_frames_count,
                            uint32_t                  max_frames_count> activate;
   Function<void,Pointer<const struct wclap_plugin> plugin> deactivate;
   Function<bool,Pointer<const struct wclap_plugin> plugin> start_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> stop_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> reset;
   Function<wclap_process_status,Pointer<const struct wclap_plugin> plugin,
                                          Pointer<const wclap_process_t>     process> process;
   Function<Pointer<const void> ,Pointer<const struct wclap_plugin> plugin, Pointer<const char> id> get_extension;
   Function<void,Pointer<const struct wclap_plugin> plugin> on_main_thread;
};
struct wclap_audio_port_info {
   wclap_id id;
   char    name[CLAP_NAME_SIZE];

   uint32_t flags;
   uint32_t channel_count;
   Pointer<const char> port_type;
   wclap_id in_place_pair;
};
struct wclap_plugin_audio_ports {
   Function<uint32_t,Pointer<const wclap_plugin_t> plugin, bool is_input> count;
   Function<bool,Pointer<const wclap_plugin_t>    plugin,
                       uint32_t                index,
                       bool                    is_input,
                       Pointer<wclap_audio_port_info_t> info> get;
};
struct wclap_host_audio_ports {
   Function<bool,Pointer<const wclap_host_t> host, uint32_t flag> is_rescan_flag_supported;
   Function<void,Pointer<const wclap_host_t> host, uint32_t flags> rescan;
};
struct wclap_audio_ports_config {
   wclap_id id;
   char    name[CLAP_NAME_SIZE];

   uint32_t input_port_count;
   uint32_t output_port_count;
   bool        has_main_input;
   uint32_t    main_input_channel_count;
   Pointer<const char> main_input_port_type;
   bool        has_main_output;
   uint32_t    main_output_channel_count;
   Pointer<const char> main_output_port_type;
};
struct wclap_plugin_audio_ports_config {
   Function<uint32_t,Pointer<const wclap_plugin_t> plugin> count;
   Function<bool,Pointer<const wclap_plugin_t>       plugin,
                       uint32_t                   index,
                       Pointer<wclap_audio_ports_config_t> config> get;
   Function<bool,Pointer<const wclap_plugin_t> plugin, wclap_id config_id> select;
};
struct wclap_plugin_audio_ports_config_info {
   Function<wclap_id,Pointer<const wclap_plugin_t> plugin> current_config;
   Function<bool,Pointer<const wclap_plugin_t>    plugin,
                       wclap_id                 config_id,
                       uint32_t                port_index,
                       bool                    is_input,
                       Pointer<wclap_audio_port_info_t> info> get;
};
struct wclap_host_audio_ports_config {
   Function<void,Pointer<const wclap_host_t> host> rescan;
};
struct wclap_version {
   uint32_t major;
   uint32_t minor;
   uint32_t revision;
};
struct wclap_host {
   wclap_version_t wclap_version;

   Pointer<void> host_data;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> version;
   Function<Pointer<const void> ,Pointer<const struct wclap_host> host, Pointer<const char> extension_id> get_extension;
   Function<void,Pointer<const struct wclap_host> host> request_restart;
   Function<void,Pointer<const struct wclap_host> host> request_process;
   Function<void,Pointer<const struct wclap_host> host> request_callback;
};
typedef int64_t wclap_beattime;
typedef int64_t wclap_sectime;
typedef uint32_t wclap_id;
typedef int32_t wclap_note_expression;
struct wclap_event_header {
   uint32_t size;
   uint32_t time;
   uint16_t space_id;
   uint16_t type;
   uint32_t flags;
};
struct wclap_event_note {
   wclap_event_header_t header;

   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;
   double  velocity;
};
struct wclap_event_note_expression {
   wclap_event_header_t header;

   wclap_note_expression expression_id;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_value {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_mod {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double amount;
};
struct wclap_event_param_gesture {
   wclap_event_header_t header;
   wclap_id param_id;
};
struct wclap_event_transport {
   wclap_event_header_t header;

   uint32_t flags;

   wclap_beattime song_pos_beats;
   wclap_sectime  song_pos_seconds;

   double tempo;
   double tempo_inc;

   wclap_beattime loop_start_beats;
   wclap_beattime loop_end_beats;
   wclap_sectime  loop_start_seconds;
   wclap_sectime  loop_end_seconds;

   wclap_beattime bar_start;
   int32_t       bar_number;

   uint16_t tsig_num;
   uint16_t tsig_denom;
};
struct wclap_event_midi {
   wclap_event_header_t header;

   uint16_t port_index;
   uint8_t  data[3];
};
struct wclap_event_midi_sysex {
   wclap_event_header_t header;

   uint16_t       port_index;
   Pointer<const uint8_t> buffer;
   uint32_t       size;
};
struct wclap_event_midi2 {
   wclap_event_header_t header;

   uint16_t port_index;
   uint32_t data[4];
};
struct wclap_input_events {
   Pointer<void> ctx;
   Function<uint32_t,Pointer<const struct wclap_input_events> list> size;
   Function<Pointer<const wclap_event_header_t> ,Pointer<const struct wclap_input_events> list, uint32_t index> get;
};
struct wclap_output_events {
   Pointer<void> ctx;
   Function<bool,Pointer<const struct wclap_output_events> list,
                            Pointer<const wclap_event_header_t>       event> try_push;
};
struct wclap_audio_buffer {
   Pointer<Pointer<float>>  data32;
   Pointer<Pointer<double>> data64;
   uint32_t channel_count;
   uint32_t latency;
   uint64_t constant_mask;
};
typedef int32_t wclap_process_status;
struct wclap_process {
   int64_t steady_time;
   uint32_t frames_count;
   Pointer<const wclap_event_transport_t> transport;
   Pointer<const wclap_audio_buffer_t> audio_inputs;
   Pointer<wclap_audio_buffer_t>       audio_outputs;
   uint32_t                   audio_inputs_count;
   uint32_t                   audio_outputs_count;
   Pointer<const wclap_input_events_t>  in_events;
   Pointer<const wclap_output_events_t> out_events;
};
struct wclap_plugin_descriptor {
   wclap_version_t wclap_version;
   Pointer<const char> id;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> manual_url;
   Pointer<const char> support_url;
   Pointer<const char> version;
   Pointer<const char> description;
   Pointer<const char> Pointer<const> features;
};
struct wclap_plugin {
   Pointer<const wclap_plugin_descriptor_t> desc;

   Pointer<void> plugin_data;
   Function<bool,Pointer<const struct wclap_plugin> plugin> init;
   Function<void,Pointer<const struct wclap_plugin> plugin> destroy;
   Function<bool,Pointer<const struct wclap_plugin> plugin,
                            double                    sample_rate,
                            uint32_t                  min_frames_count,
                            uint32_t                  max_frames_count> activate;
   Function<void,Pointer<const struct wclap_plugin> plugin> deactivate;
   Function<bool,Pointer<const struct wclap_plugin> plugin> start_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> stop_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> reset;
   Function<wclap_process_status,Pointer<const struct wclap_plugin> plugin,
                                          Pointer<const wclap_process_t>     process> process;
   Function<Pointer<const void> ,Pointer<const struct wclap_plugin> plugin, Pointer<const char> id> get_extension;
   Function<void,Pointer<const struct wclap_plugin> plugin> on_main_thread;
};
struct wclap_audio_port_info {
   wclap_id id;
   char    name[CLAP_NAME_SIZE];

   uint32_t flags;
   uint32_t channel_count;
   Pointer<const char> port_type;
   wclap_id in_place_pair;
};
struct wclap_plugin_audio_ports {
   Function<uint32_t,Pointer<const wclap_plugin_t> plugin, bool is_input> count;
   Function<bool,Pointer<const wclap_plugin_t>    plugin,
                       uint32_t                index,
                       bool                    is_input,
                       Pointer<wclap_audio_port_info_t> info> get;
};
struct wclap_host_audio_ports {
   Function<bool,Pointer<const wclap_host_t> host, uint32_t flag> is_rescan_flag_supported;
   Function<void,Pointer<const wclap_host_t> host, uint32_t flags> rescan;
};
struct wclap_version {
   uint32_t major;
   uint32_t minor;
   uint32_t revision;
};
struct wclap_host {
   wclap_version_t wclap_version;

   Pointer<void> host_data;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> version;
   Function<Pointer<const void> ,Pointer<const struct wclap_host> host, Pointer<const char> extension_id> get_extension;
   Function<void,Pointer<const struct wclap_host> host> request_restart;
   Function<void,Pointer<const struct wclap_host> host> request_process;
   Function<void,Pointer<const struct wclap_host> host> request_callback;
};
typedef int64_t wclap_beattime;
typedef int64_t wclap_sectime;
typedef uint32_t wclap_id;
typedef int32_t wclap_note_expression;
struct wclap_event_header {
   uint32_t size;
   uint32_t time;
   uint16_t space_id;
   uint16_t type;
   uint32_t flags;
};
struct wclap_event_note {
   wclap_event_header_t header;

   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;
   double  velocity;
};
struct wclap_event_note_expression {
   wclap_event_header_t header;

   wclap_note_expression expression_id;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_value {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_mod {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double amount;
};
struct wclap_event_param_gesture {
   wclap_event_header_t header;
   wclap_id param_id;
};
struct wclap_event_transport {
   wclap_event_header_t header;

   uint32_t flags;

   wclap_beattime song_pos_beats;
   wclap_sectime  song_pos_seconds;

   double tempo;
   double tempo_inc;

   wclap_beattime loop_start_beats;
   wclap_beattime loop_end_beats;
   wclap_sectime  loop_start_seconds;
   wclap_sectime  loop_end_seconds;

   wclap_beattime bar_start;
   int32_t       bar_number;

   uint16_t tsig_num;
   uint16_t tsig_denom;
};
struct wclap_event_midi {
   wclap_event_header_t header;

   uint16_t port_index;
   uint8_t  data[3];
};
struct wclap_event_midi_sysex {
   wclap_event_header_t header;

   uint16_t       port_index;
   Pointer<const uint8_t> buffer;
   uint32_t       size;
};
struct wclap_event_midi2 {
   wclap_event_header_t header;

   uint16_t port_index;
   uint32_t data[4];
};
struct wclap_input_events {
   Pointer<void> ctx;
   Function<uint32_t,Pointer<const struct wclap_input_events> list> size;
   Function<Pointer<const wclap_event_header_t> ,Pointer<const struct wclap_input_events> list, uint32_t index> get;
};
struct wclap_output_events {
   Pointer<void> ctx;
   Function<bool,Pointer<const struct wclap_output_events> list,
                            Pointer<const wclap_event_header_t>       event> try_push;
};
struct wclap_audio_buffer {
   Pointer<Pointer<float>>  data32;
   Pointer<Pointer<double>> data64;
   uint32_t channel_count;
   uint32_t latency;
   uint64_t constant_mask;
};
typedef int32_t wclap_process_status;
struct wclap_process {
   int64_t steady_time;
   uint32_t frames_count;
   Pointer<const wclap_event_transport_t> transport;
   Pointer<const wclap_audio_buffer_t> audio_inputs;
   Pointer<wclap_audio_buffer_t>       audio_outputs;
   uint32_t                   audio_inputs_count;
   uint32_t                   audio_outputs_count;
   Pointer<const wclap_input_events_t>  in_events;
   Pointer<const wclap_output_events_t> out_events;
};
struct wclap_plugin_descriptor {
   wclap_version_t wclap_version;
   Pointer<const char> id;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> manual_url;
   Pointer<const char> support_url;
   Pointer<const char> version;
   Pointer<const char> description;
   Pointer<const char> Pointer<const> features;
};
struct wclap_plugin {
   Pointer<const wclap_plugin_descriptor_t> desc;

   Pointer<void> plugin_data;
   Function<bool,Pointer<const struct wclap_plugin> plugin> init;
   Function<void,Pointer<const struct wclap_plugin> plugin> destroy;
   Function<bool,Pointer<const struct wclap_plugin> plugin,
                            double                    sample_rate,
                            uint32_t                  min_frames_count,
                            uint32_t                  max_frames_count> activate;
   Function<void,Pointer<const struct wclap_plugin> plugin> deactivate;
   Function<bool,Pointer<const struct wclap_plugin> plugin> start_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> stop_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> reset;
   Function<wclap_process_status,Pointer<const struct wclap_plugin> plugin,
                                          Pointer<const wclap_process_t>     process> process;
   Function<Pointer<const void> ,Pointer<const struct wclap_plugin> plugin, Pointer<const char> id> get_extension;
   Function<void,Pointer<const struct wclap_plugin> plugin> on_main_thread;
};
struct wclap_audio_port_info {
   wclap_id id;
   char    name[CLAP_NAME_SIZE];

   uint32_t flags;
   uint32_t channel_count;
   Pointer<const char> port_type;
   wclap_id in_place_pair;
};
struct wclap_plugin_audio_ports {
   Function<uint32_t,Pointer<const wclap_plugin_t> plugin, bool is_input> count;
   Function<bool,Pointer<const wclap_plugin_t>    plugin,
                       uint32_t                index,
                       bool                    is_input,
                       Pointer<wclap_audio_port_info_t> info> get;
};
struct wclap_host_audio_ports {
   Function<bool,Pointer<const wclap_host_t> host, uint32_t flag> is_rescan_flag_supported;
   Function<void,Pointer<const wclap_host_t> host, uint32_t flags> rescan;
};
struct wclap_audio_port_configuration_request {
   bool     is_input;
   uint32_t port_index;
   uint32_t channel_count;
   Pointer<const char> port_type;
   Pointer<const void> port_details;
};
struct wclap_plugin_configurable_audio_ports {
   Function<bool,
      Pointer<const wclap_plugin_t>                                plugin,
      Pointer<const struct wclap_audio_port_configuration_request> requests,
      uint32_t                                            request_count> can_apply_configuration;
   Function<bool,Pointer<const wclap_plugin_t>                                plugin,
                                       Pointer<const struct wclap_audio_port_configuration_request> requests,
                                       uint32_t request_count> apply_configuration;
};
struct wclap_version {
   uint32_t major;
   uint32_t minor;
   uint32_t revision;
};
struct wclap_host {
   wclap_version_t wclap_version;

   Pointer<void> host_data;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> version;
   Function<Pointer<const void> ,Pointer<const struct wclap_host> host, Pointer<const char> extension_id> get_extension;
   Function<void,Pointer<const struct wclap_host> host> request_restart;
   Function<void,Pointer<const struct wclap_host> host> request_process;
   Function<void,Pointer<const struct wclap_host> host> request_callback;
};
typedef int64_t wclap_beattime;
typedef int64_t wclap_sectime;
typedef uint32_t wclap_id;
typedef int32_t wclap_note_expression;
struct wclap_event_header {
   uint32_t size;
   uint32_t time;
   uint16_t space_id;
   uint16_t type;
   uint32_t flags;
};
struct wclap_event_note {
   wclap_event_header_t header;

   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;
   double  velocity;
};
struct wclap_event_note_expression {
   wclap_event_header_t header;

   wclap_note_expression expression_id;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_value {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_mod {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double amount;
};
struct wclap_event_param_gesture {
   wclap_event_header_t header;
   wclap_id param_id;
};
struct wclap_event_transport {
   wclap_event_header_t header;

   uint32_t flags;

   wclap_beattime song_pos_beats;
   wclap_sectime  song_pos_seconds;

   double tempo;
   double tempo_inc;

   wclap_beattime loop_start_beats;
   wclap_beattime loop_end_beats;
   wclap_sectime  loop_start_seconds;
   wclap_sectime  loop_end_seconds;

   wclap_beattime bar_start;
   int32_t       bar_number;

   uint16_t tsig_num;
   uint16_t tsig_denom;
};
struct wclap_event_midi {
   wclap_event_header_t header;

   uint16_t port_index;
   uint8_t  data[3];
};
struct wclap_event_midi_sysex {
   wclap_event_header_t header;

   uint16_t       port_index;
   Pointer<const uint8_t> buffer;
   uint32_t       size;
};
struct wclap_event_midi2 {
   wclap_event_header_t header;

   uint16_t port_index;
   uint32_t data[4];
};
struct wclap_input_events {
   Pointer<void> ctx;
   Function<uint32_t,Pointer<const struct wclap_input_events> list> size;
   Function<Pointer<const wclap_event_header_t> ,Pointer<const struct wclap_input_events> list, uint32_t index> get;
};
struct wclap_output_events {
   Pointer<void> ctx;
   Function<bool,Pointer<const struct wclap_output_events> list,
                            Pointer<const wclap_event_header_t>       event> try_push;
};
struct wclap_audio_buffer {
   Pointer<Pointer<float>>  data32;
   Pointer<Pointer<double>> data64;
   uint32_t channel_count;
   uint32_t latency;
   uint64_t constant_mask;
};
typedef int32_t wclap_process_status;
struct wclap_process {
   int64_t steady_time;
   uint32_t frames_count;
   Pointer<const wclap_event_transport_t> transport;
   Pointer<const wclap_audio_buffer_t> audio_inputs;
   Pointer<wclap_audio_buffer_t>       audio_outputs;
   uint32_t                   audio_inputs_count;
   uint32_t                   audio_outputs_count;
   Pointer<const wclap_input_events_t>  in_events;
   Pointer<const wclap_output_events_t> out_events;
};
struct wclap_plugin_descriptor {
   wclap_version_t wclap_version;
   Pointer<const char> id;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> manual_url;
   Pointer<const char> support_url;
   Pointer<const char> version;
   Pointer<const char> description;
   Pointer<const char> Pointer<const> features;
};
struct wclap_plugin {
   Pointer<const wclap_plugin_descriptor_t> desc;

   Pointer<void> plugin_data;
   Function<bool,Pointer<const struct wclap_plugin> plugin> init;
   Function<void,Pointer<const struct wclap_plugin> plugin> destroy;
   Function<bool,Pointer<const struct wclap_plugin> plugin,
                            double                    sample_rate,
                            uint32_t                  min_frames_count,
                            uint32_t                  max_frames_count> activate;
   Function<void,Pointer<const struct wclap_plugin> plugin> deactivate;
   Function<bool,Pointer<const struct wclap_plugin> plugin> start_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> stop_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> reset;
   Function<wclap_process_status,Pointer<const struct wclap_plugin> plugin,
                                          Pointer<const wclap_process_t>     process> process;
   Function<Pointer<const void> ,Pointer<const struct wclap_plugin> plugin, Pointer<const char> id> get_extension;
   Function<void,Pointer<const struct wclap_plugin> plugin> on_main_thread;
};
typedef uint32_t wclap_context_menu_item_kind_t;
struct wclap_context_menu_target {
   uint32_t kind;
   wclap_id  id;
};
struct wclap_context_menu_entry {
   Pointer<const char> label;
   bool        is_enabled;
   wclap_id     action_id;
};
struct wclap_context_menu_check_entry {
   Pointer<const char> label;
   bool        is_enabled;
   bool        is_checked;
   wclap_id     action_id;
};
struct wclap_context_menu_item_title {
   Pointer<const char> title;
   bool        is_enabled;
};
struct wclap_context_menu_submenu {
   Pointer<const char> label;
   bool        is_enabled;
};
struct wclap_context_menu_builder {
   Pointer<void> ctx;
   Function<bool,Pointer<const struct wclap_context_menu_builder> builder,
                            wclap_context_menu_item_kind_t           item_kind,
                            Pointer<const void>                             item_data> add_item;
   Function<bool,Pointer<const struct wclap_context_menu_builder> builder,
                            wclap_context_menu_item_kind_t           item_kind> supports;
};
struct wclap_plugin_context_menu {
   Function<bool,Pointer<const wclap_plugin_t>               plugin,
                            Pointer<const wclap_context_menu_target_t>  target,
                            Pointer<const wclap_context_menu_builder_t> builder> populate;
   Function<bool,Pointer<const wclap_plugin_t>              plugin,
                           Pointer<const wclap_context_menu_target_t> target,
                           wclap_id                           action_id> perform;
};
struct wclap_host_context_menu {
   Function<bool,Pointer<const wclap_host_t>                 host,
                            Pointer<const wclap_context_menu_target_t>  target,
                            Pointer<const wclap_context_menu_builder_t> builder> populate;
   Function<bool,Pointer<const wclap_host_t>                host,
                           Pointer<const wclap_context_menu_target_t> target,
                           wclap_id                           action_id> perform;
   Function<bool,Pointer<const wclap_host_t> host> can_popup;
   Function<bool,Pointer<const wclap_host_t>                host,
                         Pointer<const wclap_context_menu_target_t> target,
                         int32_t                           screen_index,
                         int32_t                           x,
                         int32_t                           y> popup;
};
struct wclap_version {
   uint32_t major;
   uint32_t minor;
   uint32_t revision;
};
struct wclap_host {
   wclap_version_t wclap_version;

   Pointer<void> host_data;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> version;
   Function<Pointer<const void> ,Pointer<const struct wclap_host> host, Pointer<const char> extension_id> get_extension;
   Function<void,Pointer<const struct wclap_host> host> request_restart;
   Function<void,Pointer<const struct wclap_host> host> request_process;
   Function<void,Pointer<const struct wclap_host> host> request_callback;
};
typedef int64_t wclap_beattime;
typedef int64_t wclap_sectime;
typedef uint32_t wclap_id;
typedef int32_t wclap_note_expression;
struct wclap_event_header {
   uint32_t size;
   uint32_t time;
   uint16_t space_id;
   uint16_t type;
   uint32_t flags;
};
struct wclap_event_note {
   wclap_event_header_t header;

   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;
   double  velocity;
};
struct wclap_event_note_expression {
   wclap_event_header_t header;

   wclap_note_expression expression_id;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_value {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_mod {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double amount;
};
struct wclap_event_param_gesture {
   wclap_event_header_t header;
   wclap_id param_id;
};
struct wclap_event_transport {
   wclap_event_header_t header;

   uint32_t flags;

   wclap_beattime song_pos_beats;
   wclap_sectime  song_pos_seconds;

   double tempo;
   double tempo_inc;

   wclap_beattime loop_start_beats;
   wclap_beattime loop_end_beats;
   wclap_sectime  loop_start_seconds;
   wclap_sectime  loop_end_seconds;

   wclap_beattime bar_start;
   int32_t       bar_number;

   uint16_t tsig_num;
   uint16_t tsig_denom;
};
struct wclap_event_midi {
   wclap_event_header_t header;

   uint16_t port_index;
   uint8_t  data[3];
};
struct wclap_event_midi_sysex {
   wclap_event_header_t header;

   uint16_t       port_index;
   Pointer<const uint8_t> buffer;
   uint32_t       size;
};
struct wclap_event_midi2 {
   wclap_event_header_t header;

   uint16_t port_index;
   uint32_t data[4];
};
struct wclap_input_events {
   Pointer<void> ctx;
   Function<uint32_t,Pointer<const struct wclap_input_events> list> size;
   Function<Pointer<const wclap_event_header_t> ,Pointer<const struct wclap_input_events> list, uint32_t index> get;
};
struct wclap_output_events {
   Pointer<void> ctx;
   Function<bool,Pointer<const struct wclap_output_events> list,
                            Pointer<const wclap_event_header_t>       event> try_push;
};
struct wclap_audio_buffer {
   Pointer<Pointer<float>>  data32;
   Pointer<Pointer<double>> data64;
   uint32_t channel_count;
   uint32_t latency;
   uint64_t constant_mask;
};
typedef int32_t wclap_process_status;
struct wclap_process {
   int64_t steady_time;
   uint32_t frames_count;
   Pointer<const wclap_event_transport_t> transport;
   Pointer<const wclap_audio_buffer_t> audio_inputs;
   Pointer<wclap_audio_buffer_t>       audio_outputs;
   uint32_t                   audio_inputs_count;
   uint32_t                   audio_outputs_count;
   Pointer<const wclap_input_events_t>  in_events;
   Pointer<const wclap_output_events_t> out_events;
};
struct wclap_plugin_descriptor {
   wclap_version_t wclap_version;
   Pointer<const char> id;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> manual_url;
   Pointer<const char> support_url;
   Pointer<const char> version;
   Pointer<const char> description;
   Pointer<const char> Pointer<const> features;
};
struct wclap_plugin {
   Pointer<const wclap_plugin_descriptor_t> desc;

   Pointer<void> plugin_data;
   Function<bool,Pointer<const struct wclap_plugin> plugin> init;
   Function<void,Pointer<const struct wclap_plugin> plugin> destroy;
   Function<bool,Pointer<const struct wclap_plugin> plugin,
                            double                    sample_rate,
                            uint32_t                  min_frames_count,
                            uint32_t                  max_frames_count> activate;
   Function<void,Pointer<const struct wclap_plugin> plugin> deactivate;
   Function<bool,Pointer<const struct wclap_plugin> plugin> start_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> stop_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> reset;
   Function<wclap_process_status,Pointer<const struct wclap_plugin> plugin,
                                          Pointer<const wclap_process_t>     process> process;
   Function<Pointer<const void> ,Pointer<const struct wclap_plugin> plugin, Pointer<const char> id> get_extension;
   Function<void,Pointer<const struct wclap_plugin> plugin> on_main_thread;
};
struct wclap_host_event_registry {
   Function<bool,Pointer<const wclap_host_t> host, Pointer<const char> space_name, Pointer<uint16_t> space_id> query;
};
struct wclap_version {
   uint32_t major;
   uint32_t minor;
   uint32_t revision;
};
struct wclap_host {
   wclap_version_t wclap_version;

   Pointer<void> host_data;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> version;
   Function<Pointer<const void> ,Pointer<const struct wclap_host> host, Pointer<const char> extension_id> get_extension;
   Function<void,Pointer<const struct wclap_host> host> request_restart;
   Function<void,Pointer<const struct wclap_host> host> request_process;
   Function<void,Pointer<const struct wclap_host> host> request_callback;
};
typedef int64_t wclap_beattime;
typedef int64_t wclap_sectime;
typedef uint32_t wclap_id;
typedef int32_t wclap_note_expression;
struct wclap_event_header {
   uint32_t size;
   uint32_t time;
   uint16_t space_id;
   uint16_t type;
   uint32_t flags;
};
struct wclap_event_note {
   wclap_event_header_t header;

   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;
   double  velocity;
};
struct wclap_event_note_expression {
   wclap_event_header_t header;

   wclap_note_expression expression_id;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_value {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_mod {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double amount;
};
struct wclap_event_param_gesture {
   wclap_event_header_t header;
   wclap_id param_id;
};
struct wclap_event_transport {
   wclap_event_header_t header;

   uint32_t flags;

   wclap_beattime song_pos_beats;
   wclap_sectime  song_pos_seconds;

   double tempo;
   double tempo_inc;

   wclap_beattime loop_start_beats;
   wclap_beattime loop_end_beats;
   wclap_sectime  loop_start_seconds;
   wclap_sectime  loop_end_seconds;

   wclap_beattime bar_start;
   int32_t       bar_number;

   uint16_t tsig_num;
   uint16_t tsig_denom;
};
struct wclap_event_midi {
   wclap_event_header_t header;

   uint16_t port_index;
   uint8_t  data[3];
};
struct wclap_event_midi_sysex {
   wclap_event_header_t header;

   uint16_t       port_index;
   Pointer<const uint8_t> buffer;
   uint32_t       size;
};
struct wclap_event_midi2 {
   wclap_event_header_t header;

   uint16_t port_index;
   uint32_t data[4];
};
struct wclap_input_events {
   Pointer<void> ctx;
   Function<uint32_t,Pointer<const struct wclap_input_events> list> size;
   Function<Pointer<const wclap_event_header_t> ,Pointer<const struct wclap_input_events> list, uint32_t index> get;
};
struct wclap_output_events {
   Pointer<void> ctx;
   Function<bool,Pointer<const struct wclap_output_events> list,
                            Pointer<const wclap_event_header_t>       event> try_push;
};
struct wclap_audio_buffer {
   Pointer<Pointer<float>>  data32;
   Pointer<Pointer<double>> data64;
   uint32_t channel_count;
   uint32_t latency;
   uint64_t constant_mask;
};
typedef int32_t wclap_process_status;
struct wclap_process {
   int64_t steady_time;
   uint32_t frames_count;
   Pointer<const wclap_event_transport_t> transport;
   Pointer<const wclap_audio_buffer_t> audio_inputs;
   Pointer<wclap_audio_buffer_t>       audio_outputs;
   uint32_t                   audio_inputs_count;
   uint32_t                   audio_outputs_count;
   Pointer<const wclap_input_events_t>  in_events;
   Pointer<const wclap_output_events_t> out_events;
};
struct wclap_plugin_descriptor {
   wclap_version_t wclap_version;
   Pointer<const char> id;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> manual_url;
   Pointer<const char> support_url;
   Pointer<const char> version;
   Pointer<const char> description;
   Pointer<const char> Pointer<const> features;
};
struct wclap_plugin {
   Pointer<const wclap_plugin_descriptor_t> desc;

   Pointer<void> plugin_data;
   Function<bool,Pointer<const struct wclap_plugin> plugin> init;
   Function<void,Pointer<const struct wclap_plugin> plugin> destroy;
   Function<bool,Pointer<const struct wclap_plugin> plugin,
                            double                    sample_rate,
                            uint32_t                  min_frames_count,
                            uint32_t                  max_frames_count> activate;
   Function<void,Pointer<const struct wclap_plugin> plugin> deactivate;
   Function<bool,Pointer<const struct wclap_plugin> plugin> start_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> stop_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> reset;
   Function<wclap_process_status,Pointer<const struct wclap_plugin> plugin,
                                          Pointer<const wclap_process_t>     process> process;
   Function<Pointer<const void> ,Pointer<const struct wclap_plugin> plugin, Pointer<const char> id> get_extension;
   Function<void,Pointer<const struct wclap_plugin> plugin> on_main_thread;
};
typedef unsigned long wclap_xwnd;
struct wclap_window {
   Pointer<const char> api;
   union {
      wclap_nsview cocoa;
      wclap_xwnd   x11;
      wclap_hwnd   win32;
      Pointer<void>       ptr;
   };
};
struct wclap_gui_resize_hints {
   bool can_resize_horizontally;
   bool can_resize_vertically;
   bool     preserve_aspect_ratio;
   uint32_t aspect_ratio_width;
   uint32_t aspect_ratio_height;
};
struct wclap_plugin_gui {
   Function<bool,Pointer<const wclap_plugin_t> plugin, Pointer<const char> api, bool is_floating> is_api_supported;
   Function<bool,Pointer<const wclap_plugin_t> plugin,
                                     Pointer<Pointer<const char>>         api,
                                     Pointer<bool>                is_floating> get_preferred_api;
   Function<bool,Pointer<const wclap_plugin_t> plugin, Pointer<const char> api, bool is_floating> create;
   Function<void,Pointer<const wclap_plugin_t> plugin> destroy;
   Function<bool,Pointer<const wclap_plugin_t> plugin, double scale> set_scale;
   Function<bool,Pointer<const wclap_plugin_t> plugin, Pointer<uint32_t> width, Pointer<uint32_t> height> get_size;
   Function<bool,Pointer<const wclap_plugin_t> plugin> can_resize;
   Function<bool,Pointer<const wclap_plugin_t> plugin, Pointer<wclap_gui_resize_hints_t> hints> get_resize_hints;
   Function<bool,Pointer<const wclap_plugin_t> plugin, Pointer<uint32_t> width, Pointer<uint32_t> height> adjust_size;
   Function<bool,Pointer<const wclap_plugin_t> plugin, uint32_t width, uint32_t height> set_size;
   Function<bool,Pointer<const wclap_plugin_t> plugin, Pointer<const wclap_window_t> window> set_parent;
   Function<bool,Pointer<const wclap_plugin_t> plugin, Pointer<const wclap_window_t> window> set_transient;
   Function<void,Pointer<const wclap_plugin_t> plugin, Pointer<const char> title> suggest_title;
   Function<bool,Pointer<const wclap_plugin_t> plugin> show;
   Function<bool,Pointer<const wclap_plugin_t> plugin> hide;
};
struct wclap_host_gui {
   Function<void,Pointer<const wclap_host_t> host> resize_hints_changed;
   Function<bool,Pointer<const wclap_host_t> host, uint32_t width, uint32_t height> request_resize;
   Function<bool,Pointer<const wclap_host_t> host> request_show;
   Function<bool,Pointer<const wclap_host_t> host> request_hide;
   Function<void,Pointer<const wclap_host_t> host, bool was_destroyed> closed;
};
struct wclap_version {
   uint32_t major;
   uint32_t minor;
   uint32_t revision;
};
struct wclap_host {
   wclap_version_t wclap_version;

   Pointer<void> host_data;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> version;
   Function<Pointer<const void> ,Pointer<const struct wclap_host> host, Pointer<const char> extension_id> get_extension;
   Function<void,Pointer<const struct wclap_host> host> request_restart;
   Function<void,Pointer<const struct wclap_host> host> request_process;
   Function<void,Pointer<const struct wclap_host> host> request_callback;
};
typedef int64_t wclap_beattime;
typedef int64_t wclap_sectime;
typedef uint32_t wclap_id;
typedef int32_t wclap_note_expression;
struct wclap_event_header {
   uint32_t size;
   uint32_t time;
   uint16_t space_id;
   uint16_t type;
   uint32_t flags;
};
struct wclap_event_note {
   wclap_event_header_t header;

   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;
   double  velocity;
};
struct wclap_event_note_expression {
   wclap_event_header_t header;

   wclap_note_expression expression_id;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_value {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_mod {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double amount;
};
struct wclap_event_param_gesture {
   wclap_event_header_t header;
   wclap_id param_id;
};
struct wclap_event_transport {
   wclap_event_header_t header;

   uint32_t flags;

   wclap_beattime song_pos_beats;
   wclap_sectime  song_pos_seconds;

   double tempo;
   double tempo_inc;

   wclap_beattime loop_start_beats;
   wclap_beattime loop_end_beats;
   wclap_sectime  loop_start_seconds;
   wclap_sectime  loop_end_seconds;

   wclap_beattime bar_start;
   int32_t       bar_number;

   uint16_t tsig_num;
   uint16_t tsig_denom;
};
struct wclap_event_midi {
   wclap_event_header_t header;

   uint16_t port_index;
   uint8_t  data[3];
};
struct wclap_event_midi_sysex {
   wclap_event_header_t header;

   uint16_t       port_index;
   Pointer<const uint8_t> buffer;
   uint32_t       size;
};
struct wclap_event_midi2 {
   wclap_event_header_t header;

   uint16_t port_index;
   uint32_t data[4];
};
struct wclap_input_events {
   Pointer<void> ctx;
   Function<uint32_t,Pointer<const struct wclap_input_events> list> size;
   Function<Pointer<const wclap_event_header_t> ,Pointer<const struct wclap_input_events> list, uint32_t index> get;
};
struct wclap_output_events {
   Pointer<void> ctx;
   Function<bool,Pointer<const struct wclap_output_events> list,
                            Pointer<const wclap_event_header_t>       event> try_push;
};
struct wclap_audio_buffer {
   Pointer<Pointer<float>>  data32;
   Pointer<Pointer<double>> data64;
   uint32_t channel_count;
   uint32_t latency;
   uint64_t constant_mask;
};
typedef int32_t wclap_process_status;
struct wclap_process {
   int64_t steady_time;
   uint32_t frames_count;
   Pointer<const wclap_event_transport_t> transport;
   Pointer<const wclap_audio_buffer_t> audio_inputs;
   Pointer<wclap_audio_buffer_t>       audio_outputs;
   uint32_t                   audio_inputs_count;
   uint32_t                   audio_outputs_count;
   Pointer<const wclap_input_events_t>  in_events;
   Pointer<const wclap_output_events_t> out_events;
};
struct wclap_plugin_descriptor {
   wclap_version_t wclap_version;
   Pointer<const char> id;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> manual_url;
   Pointer<const char> support_url;
   Pointer<const char> version;
   Pointer<const char> description;
   Pointer<const char> Pointer<const> features;
};
struct wclap_plugin {
   Pointer<const wclap_plugin_descriptor_t> desc;

   Pointer<void> plugin_data;
   Function<bool,Pointer<const struct wclap_plugin> plugin> init;
   Function<void,Pointer<const struct wclap_plugin> plugin> destroy;
   Function<bool,Pointer<const struct wclap_plugin> plugin,
                            double                    sample_rate,
                            uint32_t                  min_frames_count,
                            uint32_t                  max_frames_count> activate;
   Function<void,Pointer<const struct wclap_plugin> plugin> deactivate;
   Function<bool,Pointer<const struct wclap_plugin> plugin> start_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> stop_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> reset;
   Function<wclap_process_status,Pointer<const struct wclap_plugin> plugin,
                                          Pointer<const wclap_process_t>     process> process;
   Function<Pointer<const void> ,Pointer<const struct wclap_plugin> plugin, Pointer<const char> id> get_extension;
   Function<void,Pointer<const struct wclap_plugin> plugin> on_main_thread;
};
struct wclap_plugin_latency {
   Function<uint32_t,Pointer<const wclap_plugin_t> plugin> get;
};
struct wclap_host_latency {
   Function<void,Pointer<const wclap_host_t> host> changed;
};
struct wclap_version {
   uint32_t major;
   uint32_t minor;
   uint32_t revision;
};
struct wclap_host {
   wclap_version_t wclap_version;

   Pointer<void> host_data;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> version;
   Function<Pointer<const void> ,Pointer<const struct wclap_host> host, Pointer<const char> extension_id> get_extension;
   Function<void,Pointer<const struct wclap_host> host> request_restart;
   Function<void,Pointer<const struct wclap_host> host> request_process;
   Function<void,Pointer<const struct wclap_host> host> request_callback;
};
typedef int64_t wclap_beattime;
typedef int64_t wclap_sectime;
typedef uint32_t wclap_id;
typedef int32_t wclap_note_expression;
struct wclap_event_header {
   uint32_t size;
   uint32_t time;
   uint16_t space_id;
   uint16_t type;
   uint32_t flags;
};
struct wclap_event_note {
   wclap_event_header_t header;

   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;
   double  velocity;
};
struct wclap_event_note_expression {
   wclap_event_header_t header;

   wclap_note_expression expression_id;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_value {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_mod {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double amount;
};
struct wclap_event_param_gesture {
   wclap_event_header_t header;
   wclap_id param_id;
};
struct wclap_event_transport {
   wclap_event_header_t header;

   uint32_t flags;

   wclap_beattime song_pos_beats;
   wclap_sectime  song_pos_seconds;

   double tempo;
   double tempo_inc;

   wclap_beattime loop_start_beats;
   wclap_beattime loop_end_beats;
   wclap_sectime  loop_start_seconds;
   wclap_sectime  loop_end_seconds;

   wclap_beattime bar_start;
   int32_t       bar_number;

   uint16_t tsig_num;
   uint16_t tsig_denom;
};
struct wclap_event_midi {
   wclap_event_header_t header;

   uint16_t port_index;
   uint8_t  data[3];
};
struct wclap_event_midi_sysex {
   wclap_event_header_t header;

   uint16_t       port_index;
   Pointer<const uint8_t> buffer;
   uint32_t       size;
};
struct wclap_event_midi2 {
   wclap_event_header_t header;

   uint16_t port_index;
   uint32_t data[4];
};
struct wclap_input_events {
   Pointer<void> ctx;
   Function<uint32_t,Pointer<const struct wclap_input_events> list> size;
   Function<Pointer<const wclap_event_header_t> ,Pointer<const struct wclap_input_events> list, uint32_t index> get;
};
struct wclap_output_events {
   Pointer<void> ctx;
   Function<bool,Pointer<const struct wclap_output_events> list,
                            Pointer<const wclap_event_header_t>       event> try_push;
};
struct wclap_audio_buffer {
   Pointer<Pointer<float>>  data32;
   Pointer<Pointer<double>> data64;
   uint32_t channel_count;
   uint32_t latency;
   uint64_t constant_mask;
};
typedef int32_t wclap_process_status;
struct wclap_process {
   int64_t steady_time;
   uint32_t frames_count;
   Pointer<const wclap_event_transport_t> transport;
   Pointer<const wclap_audio_buffer_t> audio_inputs;
   Pointer<wclap_audio_buffer_t>       audio_outputs;
   uint32_t                   audio_inputs_count;
   uint32_t                   audio_outputs_count;
   Pointer<const wclap_input_events_t>  in_events;
   Pointer<const wclap_output_events_t> out_events;
};
struct wclap_plugin_descriptor {
   wclap_version_t wclap_version;
   Pointer<const char> id;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> manual_url;
   Pointer<const char> support_url;
   Pointer<const char> version;
   Pointer<const char> description;
   Pointer<const char> Pointer<const> features;
};
struct wclap_plugin {
   Pointer<const wclap_plugin_descriptor_t> desc;

   Pointer<void> plugin_data;
   Function<bool,Pointer<const struct wclap_plugin> plugin> init;
   Function<void,Pointer<const struct wclap_plugin> plugin> destroy;
   Function<bool,Pointer<const struct wclap_plugin> plugin,
                            double                    sample_rate,
                            uint32_t                  min_frames_count,
                            uint32_t                  max_frames_count> activate;
   Function<void,Pointer<const struct wclap_plugin> plugin> deactivate;
   Function<bool,Pointer<const struct wclap_plugin> plugin> start_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> stop_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> reset;
   Function<wclap_process_status,Pointer<const struct wclap_plugin> plugin,
                                          Pointer<const wclap_process_t>     process> process;
   Function<Pointer<const void> ,Pointer<const struct wclap_plugin> plugin, Pointer<const char> id> get_extension;
   Function<void,Pointer<const struct wclap_plugin> plugin> on_main_thread;
};
typedef int32_t wclap_log_severity;
struct wclap_host_log {
   Function<void,Pointer<const wclap_host_t> host, wclap_log_severity severity, Pointer<const char> msg> log;
};
struct wclap_version {
   uint32_t major;
   uint32_t minor;
   uint32_t revision;
};
struct wclap_host {
   wclap_version_t wclap_version;

   Pointer<void> host_data;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> version;
   Function<Pointer<const void> ,Pointer<const struct wclap_host> host, Pointer<const char> extension_id> get_extension;
   Function<void,Pointer<const struct wclap_host> host> request_restart;
   Function<void,Pointer<const struct wclap_host> host> request_process;
   Function<void,Pointer<const struct wclap_host> host> request_callback;
};
typedef int64_t wclap_beattime;
typedef int64_t wclap_sectime;
typedef uint32_t wclap_id;
typedef int32_t wclap_note_expression;
struct wclap_event_header {
   uint32_t size;
   uint32_t time;
   uint16_t space_id;
   uint16_t type;
   uint32_t flags;
};
struct wclap_event_note {
   wclap_event_header_t header;

   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;
   double  velocity;
};
struct wclap_event_note_expression {
   wclap_event_header_t header;

   wclap_note_expression expression_id;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_value {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_mod {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double amount;
};
struct wclap_event_param_gesture {
   wclap_event_header_t header;
   wclap_id param_id;
};
struct wclap_event_transport {
   wclap_event_header_t header;

   uint32_t flags;

   wclap_beattime song_pos_beats;
   wclap_sectime  song_pos_seconds;

   double tempo;
   double tempo_inc;

   wclap_beattime loop_start_beats;
   wclap_beattime loop_end_beats;
   wclap_sectime  loop_start_seconds;
   wclap_sectime  loop_end_seconds;

   wclap_beattime bar_start;
   int32_t       bar_number;

   uint16_t tsig_num;
   uint16_t tsig_denom;
};
struct wclap_event_midi {
   wclap_event_header_t header;

   uint16_t port_index;
   uint8_t  data[3];
};
struct wclap_event_midi_sysex {
   wclap_event_header_t header;

   uint16_t       port_index;
   Pointer<const uint8_t> buffer;
   uint32_t       size;
};
struct wclap_event_midi2 {
   wclap_event_header_t header;

   uint16_t port_index;
   uint32_t data[4];
};
struct wclap_input_events {
   Pointer<void> ctx;
   Function<uint32_t,Pointer<const struct wclap_input_events> list> size;
   Function<Pointer<const wclap_event_header_t> ,Pointer<const struct wclap_input_events> list, uint32_t index> get;
};
struct wclap_output_events {
   Pointer<void> ctx;
   Function<bool,Pointer<const struct wclap_output_events> list,
                            Pointer<const wclap_event_header_t>       event> try_push;
};
struct wclap_audio_buffer {
   Pointer<Pointer<float>>  data32;
   Pointer<Pointer<double>> data64;
   uint32_t channel_count;
   uint32_t latency;
   uint64_t constant_mask;
};
typedef int32_t wclap_process_status;
struct wclap_process {
   int64_t steady_time;
   uint32_t frames_count;
   Pointer<const wclap_event_transport_t> transport;
   Pointer<const wclap_audio_buffer_t> audio_inputs;
   Pointer<wclap_audio_buffer_t>       audio_outputs;
   uint32_t                   audio_inputs_count;
   uint32_t                   audio_outputs_count;
   Pointer<const wclap_input_events_t>  in_events;
   Pointer<const wclap_output_events_t> out_events;
};
struct wclap_plugin_descriptor {
   wclap_version_t wclap_version;
   Pointer<const char> id;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> manual_url;
   Pointer<const char> support_url;
   Pointer<const char> version;
   Pointer<const char> description;
   Pointer<const char> Pointer<const> features;
};
struct wclap_plugin {
   Pointer<const wclap_plugin_descriptor_t> desc;

   Pointer<void> plugin_data;
   Function<bool,Pointer<const struct wclap_plugin> plugin> init;
   Function<void,Pointer<const struct wclap_plugin> plugin> destroy;
   Function<bool,Pointer<const struct wclap_plugin> plugin,
                            double                    sample_rate,
                            uint32_t                  min_frames_count,
                            uint32_t                  max_frames_count> activate;
   Function<void,Pointer<const struct wclap_plugin> plugin> deactivate;
   Function<bool,Pointer<const struct wclap_plugin> plugin> start_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> stop_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> reset;
   Function<wclap_process_status,Pointer<const struct wclap_plugin> plugin,
                                          Pointer<const wclap_process_t>     process> process;
   Function<Pointer<const void> ,Pointer<const struct wclap_plugin> plugin, Pointer<const char> id> get_extension;
   Function<void,Pointer<const struct wclap_plugin> plugin> on_main_thread;
};
struct wclap_note_name {
   char    name[CLAP_NAME_SIZE];
   int16_t port;
   int16_t key;
   int16_t channel;
};
struct wclap_plugin_note_name {
   Function<uint32_t,Pointer<const wclap_plugin_t> plugin> count;
   Function<bool,Pointer<const wclap_plugin_t> plugin, uint32_t index, Pointer<wclap_note_name_t> note_name> get;
};
struct wclap_host_note_name {
   Function<void,Pointer<const wclap_host_t> host> changed;
};
struct wclap_version {
   uint32_t major;
   uint32_t minor;
   uint32_t revision;
};
struct wclap_host {
   wclap_version_t wclap_version;

   Pointer<void> host_data;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> version;
   Function<Pointer<const void> ,Pointer<const struct wclap_host> host, Pointer<const char> extension_id> get_extension;
   Function<void,Pointer<const struct wclap_host> host> request_restart;
   Function<void,Pointer<const struct wclap_host> host> request_process;
   Function<void,Pointer<const struct wclap_host> host> request_callback;
};
typedef int64_t wclap_beattime;
typedef int64_t wclap_sectime;
typedef uint32_t wclap_id;
typedef int32_t wclap_note_expression;
struct wclap_event_header {
   uint32_t size;
   uint32_t time;
   uint16_t space_id;
   uint16_t type;
   uint32_t flags;
};
struct wclap_event_note {
   wclap_event_header_t header;

   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;
   double  velocity;
};
struct wclap_event_note_expression {
   wclap_event_header_t header;

   wclap_note_expression expression_id;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_value {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_mod {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double amount;
};
struct wclap_event_param_gesture {
   wclap_event_header_t header;
   wclap_id param_id;
};
struct wclap_event_transport {
   wclap_event_header_t header;

   uint32_t flags;

   wclap_beattime song_pos_beats;
   wclap_sectime  song_pos_seconds;

   double tempo;
   double tempo_inc;

   wclap_beattime loop_start_beats;
   wclap_beattime loop_end_beats;
   wclap_sectime  loop_start_seconds;
   wclap_sectime  loop_end_seconds;

   wclap_beattime bar_start;
   int32_t       bar_number;

   uint16_t tsig_num;
   uint16_t tsig_denom;
};
struct wclap_event_midi {
   wclap_event_header_t header;

   uint16_t port_index;
   uint8_t  data[3];
};
struct wclap_event_midi_sysex {
   wclap_event_header_t header;

   uint16_t       port_index;
   Pointer<const uint8_t> buffer;
   uint32_t       size;
};
struct wclap_event_midi2 {
   wclap_event_header_t header;

   uint16_t port_index;
   uint32_t data[4];
};
struct wclap_input_events {
   Pointer<void> ctx;
   Function<uint32_t,Pointer<const struct wclap_input_events> list> size;
   Function<Pointer<const wclap_event_header_t> ,Pointer<const struct wclap_input_events> list, uint32_t index> get;
};
struct wclap_output_events {
   Pointer<void> ctx;
   Function<bool,Pointer<const struct wclap_output_events> list,
                            Pointer<const wclap_event_header_t>       event> try_push;
};
struct wclap_audio_buffer {
   Pointer<Pointer<float>>  data32;
   Pointer<Pointer<double>> data64;
   uint32_t channel_count;
   uint32_t latency;
   uint64_t constant_mask;
};
typedef int32_t wclap_process_status;
struct wclap_process {
   int64_t steady_time;
   uint32_t frames_count;
   Pointer<const wclap_event_transport_t> transport;
   Pointer<const wclap_audio_buffer_t> audio_inputs;
   Pointer<wclap_audio_buffer_t>       audio_outputs;
   uint32_t                   audio_inputs_count;
   uint32_t                   audio_outputs_count;
   Pointer<const wclap_input_events_t>  in_events;
   Pointer<const wclap_output_events_t> out_events;
};
struct wclap_plugin_descriptor {
   wclap_version_t wclap_version;
   Pointer<const char> id;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> manual_url;
   Pointer<const char> support_url;
   Pointer<const char> version;
   Pointer<const char> description;
   Pointer<const char> Pointer<const> features;
};
struct wclap_plugin {
   Pointer<const wclap_plugin_descriptor_t> desc;

   Pointer<void> plugin_data;
   Function<bool,Pointer<const struct wclap_plugin> plugin> init;
   Function<void,Pointer<const struct wclap_plugin> plugin> destroy;
   Function<bool,Pointer<const struct wclap_plugin> plugin,
                            double                    sample_rate,
                            uint32_t                  min_frames_count,
                            uint32_t                  max_frames_count> activate;
   Function<void,Pointer<const struct wclap_plugin> plugin> deactivate;
   Function<bool,Pointer<const struct wclap_plugin> plugin> start_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> stop_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> reset;
   Function<wclap_process_status,Pointer<const struct wclap_plugin> plugin,
                                          Pointer<const wclap_process_t>     process> process;
   Function<Pointer<const void> ,Pointer<const struct wclap_plugin> plugin, Pointer<const char> id> get_extension;
   Function<void,Pointer<const struct wclap_plugin> plugin> on_main_thread;
};
struct wclap_note_port_info {
   wclap_id  id;
   uint32_t supported_dialects;
   uint32_t preferred_dialect;
   char     name[CLAP_NAME_SIZE];
};
struct wclap_plugin_note_ports {
   Function<uint32_t,Pointer<const wclap_plugin_t> plugin, bool is_input> count;
   Function<bool,Pointer<const wclap_plugin_t>   plugin,
                       uint32_t               index,
                       bool                   is_input,
                       Pointer<wclap_note_port_info_t> info> get;
};
struct wclap_host_note_ports {
   Function<uint32_t,Pointer<const wclap_host_t> host> supported_dialects;
   Function<void,Pointer<const wclap_host_t> host, uint32_t flags> rescan;
};
struct wclap_version {
   uint32_t major;
   uint32_t minor;
   uint32_t revision;
};
struct wclap_host {
   wclap_version_t wclap_version;

   Pointer<void> host_data;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> version;
   Function<Pointer<const void> ,Pointer<const struct wclap_host> host, Pointer<const char> extension_id> get_extension;
   Function<void,Pointer<const struct wclap_host> host> request_restart;
   Function<void,Pointer<const struct wclap_host> host> request_process;
   Function<void,Pointer<const struct wclap_host> host> request_callback;
};
typedef int64_t wclap_beattime;
typedef int64_t wclap_sectime;
typedef uint32_t wclap_id;
typedef int32_t wclap_note_expression;
struct wclap_event_header {
   uint32_t size;
   uint32_t time;
   uint16_t space_id;
   uint16_t type;
   uint32_t flags;
};
struct wclap_event_note {
   wclap_event_header_t header;

   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;
   double  velocity;
};
struct wclap_event_note_expression {
   wclap_event_header_t header;

   wclap_note_expression expression_id;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_value {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_mod {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double amount;
};
struct wclap_event_param_gesture {
   wclap_event_header_t header;
   wclap_id param_id;
};
struct wclap_event_transport {
   wclap_event_header_t header;

   uint32_t flags;

   wclap_beattime song_pos_beats;
   wclap_sectime  song_pos_seconds;

   double tempo;
   double tempo_inc;

   wclap_beattime loop_start_beats;
   wclap_beattime loop_end_beats;
   wclap_sectime  loop_start_seconds;
   wclap_sectime  loop_end_seconds;

   wclap_beattime bar_start;
   int32_t       bar_number;

   uint16_t tsig_num;
   uint16_t tsig_denom;
};
struct wclap_event_midi {
   wclap_event_header_t header;

   uint16_t port_index;
   uint8_t  data[3];
};
struct wclap_event_midi_sysex {
   wclap_event_header_t header;

   uint16_t       port_index;
   Pointer<const uint8_t> buffer;
   uint32_t       size;
};
struct wclap_event_midi2 {
   wclap_event_header_t header;

   uint16_t port_index;
   uint32_t data[4];
};
struct wclap_input_events {
   Pointer<void> ctx;
   Function<uint32_t,Pointer<const struct wclap_input_events> list> size;
   Function<Pointer<const wclap_event_header_t> ,Pointer<const struct wclap_input_events> list, uint32_t index> get;
};
struct wclap_output_events {
   Pointer<void> ctx;
   Function<bool,Pointer<const struct wclap_output_events> list,
                            Pointer<const wclap_event_header_t>       event> try_push;
};
struct wclap_audio_buffer {
   Pointer<Pointer<float>>  data32;
   Pointer<Pointer<double>> data64;
   uint32_t channel_count;
   uint32_t latency;
   uint64_t constant_mask;
};
typedef int32_t wclap_process_status;
struct wclap_process {
   int64_t steady_time;
   uint32_t frames_count;
   Pointer<const wclap_event_transport_t> transport;
   Pointer<const wclap_audio_buffer_t> audio_inputs;
   Pointer<wclap_audio_buffer_t>       audio_outputs;
   uint32_t                   audio_inputs_count;
   uint32_t                   audio_outputs_count;
   Pointer<const wclap_input_events_t>  in_events;
   Pointer<const wclap_output_events_t> out_events;
};
struct wclap_plugin_descriptor {
   wclap_version_t wclap_version;
   Pointer<const char> id;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> manual_url;
   Pointer<const char> support_url;
   Pointer<const char> version;
   Pointer<const char> description;
   Pointer<const char> Pointer<const> features;
};
struct wclap_plugin {
   Pointer<const wclap_plugin_descriptor_t> desc;

   Pointer<void> plugin_data;
   Function<bool,Pointer<const struct wclap_plugin> plugin> init;
   Function<void,Pointer<const struct wclap_plugin> plugin> destroy;
   Function<bool,Pointer<const struct wclap_plugin> plugin,
                            double                    sample_rate,
                            uint32_t                  min_frames_count,
                            uint32_t                  max_frames_count> activate;
   Function<void,Pointer<const struct wclap_plugin> plugin> deactivate;
   Function<bool,Pointer<const struct wclap_plugin> plugin> start_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> stop_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> reset;
   Function<wclap_process_status,Pointer<const struct wclap_plugin> plugin,
                                          Pointer<const wclap_process_t>     process> process;
   Function<Pointer<const void> ,Pointer<const struct wclap_plugin> plugin, Pointer<const char> id> get_extension;
   Function<void,Pointer<const struct wclap_plugin> plugin> on_main_thread;
};
typedef uint32_t wclap_param_info_flags;
typedef uint32_t wclap_param_rescan_flags;
typedef uint32_t wclap_param_clear_flags;
struct wclap_param_info {
   wclap_id id;

   wclap_param_info_flags flags;
   Pointer<void> cookie;
   char name[CLAP_NAME_SIZE];
   char module[CLAP_PATH_SIZE];

   double min_value;
   double max_value;
   double default_value;
};
struct wclap_plugin_params {
   Function<uint32_t,Pointer<const wclap_plugin_t> plugin> count;
   Function<bool,Pointer<const wclap_plugin_t> plugin,
                            uint32_t             param_index,
                            Pointer<wclap_param_info_t>   param_info> get_info;
   Function<bool,Pointer<const wclap_plugin_t> plugin, wclap_id param_id, Pointer<double> out_value> get_value;
   Function<bool,Pointer<const wclap_plugin_t> plugin,
                                 wclap_id              param_id,
                                 double               value,
                                 Pointer<char>                out_buffer,
                                 uint32_t             out_buffer_capacity> value_to_text;
   Function<bool,Pointer<const wclap_plugin_t> plugin,
                                 wclap_id              param_id,
                                 Pointer<const char>          param_value_text,
                                 Pointer<double>              out_value> text_to_value;
   Function<void,Pointer<const wclap_plugin_t>        plugin,
                         Pointer<const wclap_input_events_t>  in,
                         Pointer<const wclap_output_events_t> out> flush;
};
struct wclap_host_params {
   Function<void,Pointer<const wclap_host_t> host, wclap_param_rescan_flags flags> rescan;
   Function<void,Pointer<const wclap_host_t> host, wclap_id param_id, wclap_param_clear_flags flags> clear;
   Function<void,Pointer<const wclap_host_t> host> request_flush;
};
struct wclap_color {
   uint8_t alpha;
   uint8_t red;
   uint8_t green;
   uint8_t blue;
};
struct wclap_plugin_param_indication {
   Function<void,Pointer<const wclap_plugin_t> plugin,
                               wclap_id              param_id,
                               bool                 has_mapping,
                               Pointer<const wclap_color_t>  color,
                               Pointer<const char>          label,
                               Pointer<const char>          description> set_mapping;
   Function<void,Pointer<const wclap_plugin_t> plugin,
                                  wclap_id              param_id,
                                  uint32_t             automation_state,
                                  Pointer<const wclap_color_t>  color> set_automation;
};
struct wclap_version {
   uint32_t major;
   uint32_t minor;
   uint32_t revision;
};
struct wclap_host {
   wclap_version_t wclap_version;

   Pointer<void> host_data;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> version;
   Function<Pointer<const void> ,Pointer<const struct wclap_host> host, Pointer<const char> extension_id> get_extension;
   Function<void,Pointer<const struct wclap_host> host> request_restart;
   Function<void,Pointer<const struct wclap_host> host> request_process;
   Function<void,Pointer<const struct wclap_host> host> request_callback;
};
typedef int64_t wclap_beattime;
typedef int64_t wclap_sectime;
typedef uint32_t wclap_id;
typedef int32_t wclap_note_expression;
struct wclap_event_header {
   uint32_t size;
   uint32_t time;
   uint16_t space_id;
   uint16_t type;
   uint32_t flags;
};
struct wclap_event_note {
   wclap_event_header_t header;

   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;
   double  velocity;
};
struct wclap_event_note_expression {
   wclap_event_header_t header;

   wclap_note_expression expression_id;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_value {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_mod {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double amount;
};
struct wclap_event_param_gesture {
   wclap_event_header_t header;
   wclap_id param_id;
};
struct wclap_event_transport {
   wclap_event_header_t header;

   uint32_t flags;

   wclap_beattime song_pos_beats;
   wclap_sectime  song_pos_seconds;

   double tempo;
   double tempo_inc;

   wclap_beattime loop_start_beats;
   wclap_beattime loop_end_beats;
   wclap_sectime  loop_start_seconds;
   wclap_sectime  loop_end_seconds;

   wclap_beattime bar_start;
   int32_t       bar_number;

   uint16_t tsig_num;
   uint16_t tsig_denom;
};
struct wclap_event_midi {
   wclap_event_header_t header;

   uint16_t port_index;
   uint8_t  data[3];
};
struct wclap_event_midi_sysex {
   wclap_event_header_t header;

   uint16_t       port_index;
   Pointer<const uint8_t> buffer;
   uint32_t       size;
};
struct wclap_event_midi2 {
   wclap_event_header_t header;

   uint16_t port_index;
   uint32_t data[4];
};
struct wclap_input_events {
   Pointer<void> ctx;
   Function<uint32_t,Pointer<const struct wclap_input_events> list> size;
   Function<Pointer<const wclap_event_header_t> ,Pointer<const struct wclap_input_events> list, uint32_t index> get;
};
struct wclap_output_events {
   Pointer<void> ctx;
   Function<bool,Pointer<const struct wclap_output_events> list,
                            Pointer<const wclap_event_header_t>       event> try_push;
};
struct wclap_audio_buffer {
   Pointer<Pointer<float>>  data32;
   Pointer<Pointer<double>> data64;
   uint32_t channel_count;
   uint32_t latency;
   uint64_t constant_mask;
};
typedef int32_t wclap_process_status;
struct wclap_process {
   int64_t steady_time;
   uint32_t frames_count;
   Pointer<const wclap_event_transport_t> transport;
   Pointer<const wclap_audio_buffer_t> audio_inputs;
   Pointer<wclap_audio_buffer_t>       audio_outputs;
   uint32_t                   audio_inputs_count;
   uint32_t                   audio_outputs_count;
   Pointer<const wclap_input_events_t>  in_events;
   Pointer<const wclap_output_events_t> out_events;
};
struct wclap_plugin_descriptor {
   wclap_version_t wclap_version;
   Pointer<const char> id;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> manual_url;
   Pointer<const char> support_url;
   Pointer<const char> version;
   Pointer<const char> description;
   Pointer<const char> Pointer<const> features;
};
struct wclap_plugin {
   Pointer<const wclap_plugin_descriptor_t> desc;

   Pointer<void> plugin_data;
   Function<bool,Pointer<const struct wclap_plugin> plugin> init;
   Function<void,Pointer<const struct wclap_plugin> plugin> destroy;
   Function<bool,Pointer<const struct wclap_plugin> plugin,
                            double                    sample_rate,
                            uint32_t                  min_frames_count,
                            uint32_t                  max_frames_count> activate;
   Function<void,Pointer<const struct wclap_plugin> plugin> deactivate;
   Function<bool,Pointer<const struct wclap_plugin> plugin> start_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> stop_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> reset;
   Function<wclap_process_status,Pointer<const struct wclap_plugin> plugin,
                                          Pointer<const wclap_process_t>     process> process;
   Function<Pointer<const void> ,Pointer<const struct wclap_plugin> plugin, Pointer<const char> id> get_extension;
   Function<void,Pointer<const struct wclap_plugin> plugin> on_main_thread;
};
typedef uint32_t wclap_param_info_flags;
typedef uint32_t wclap_param_rescan_flags;
typedef uint32_t wclap_param_clear_flags;
struct wclap_param_info {
   wclap_id id;

   wclap_param_info_flags flags;
   Pointer<void> cookie;
   char name[CLAP_NAME_SIZE];
   char module[CLAP_PATH_SIZE];

   double min_value;
   double max_value;
   double default_value;
};
struct wclap_plugin_params {
   Function<uint32_t,Pointer<const wclap_plugin_t> plugin> count;
   Function<bool,Pointer<const wclap_plugin_t> plugin,
                            uint32_t             param_index,
                            Pointer<wclap_param_info_t>   param_info> get_info;
   Function<bool,Pointer<const wclap_plugin_t> plugin, wclap_id param_id, Pointer<double> out_value> get_value;
   Function<bool,Pointer<const wclap_plugin_t> plugin,
                                 wclap_id              param_id,
                                 double               value,
                                 Pointer<char>                out_buffer,
                                 uint32_t             out_buffer_capacity> value_to_text;
   Function<bool,Pointer<const wclap_plugin_t> plugin,
                                 wclap_id              param_id,
                                 Pointer<const char>          param_value_text,
                                 Pointer<double>              out_value> text_to_value;
   Function<void,Pointer<const wclap_plugin_t>        plugin,
                         Pointer<const wclap_input_events_t>  in,
                         Pointer<const wclap_output_events_t> out> flush;
};
struct wclap_host_params {
   Function<void,Pointer<const wclap_host_t> host, wclap_param_rescan_flags flags> rescan;
   Function<void,Pointer<const wclap_host_t> host, wclap_id param_id, wclap_param_clear_flags flags> clear;
   Function<void,Pointer<const wclap_host_t> host> request_flush;
};
struct wclap_version {
   uint32_t major;
   uint32_t minor;
   uint32_t revision;
};
struct wclap_host {
   wclap_version_t wclap_version;

   Pointer<void> host_data;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> version;
   Function<Pointer<const void> ,Pointer<const struct wclap_host> host, Pointer<const char> extension_id> get_extension;
   Function<void,Pointer<const struct wclap_host> host> request_restart;
   Function<void,Pointer<const struct wclap_host> host> request_process;
   Function<void,Pointer<const struct wclap_host> host> request_callback;
};
typedef int64_t wclap_beattime;
typedef int64_t wclap_sectime;
typedef uint32_t wclap_id;
typedef int32_t wclap_note_expression;
struct wclap_event_header {
   uint32_t size;
   uint32_t time;
   uint16_t space_id;
   uint16_t type;
   uint32_t flags;
};
struct wclap_event_note {
   wclap_event_header_t header;

   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;
   double  velocity;
};
struct wclap_event_note_expression {
   wclap_event_header_t header;

   wclap_note_expression expression_id;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_value {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_mod {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double amount;
};
struct wclap_event_param_gesture {
   wclap_event_header_t header;
   wclap_id param_id;
};
struct wclap_event_transport {
   wclap_event_header_t header;

   uint32_t flags;

   wclap_beattime song_pos_beats;
   wclap_sectime  song_pos_seconds;

   double tempo;
   double tempo_inc;

   wclap_beattime loop_start_beats;
   wclap_beattime loop_end_beats;
   wclap_sectime  loop_start_seconds;
   wclap_sectime  loop_end_seconds;

   wclap_beattime bar_start;
   int32_t       bar_number;

   uint16_t tsig_num;
   uint16_t tsig_denom;
};
struct wclap_event_midi {
   wclap_event_header_t header;

   uint16_t port_index;
   uint8_t  data[3];
};
struct wclap_event_midi_sysex {
   wclap_event_header_t header;

   uint16_t       port_index;
   Pointer<const uint8_t> buffer;
   uint32_t       size;
};
struct wclap_event_midi2 {
   wclap_event_header_t header;

   uint16_t port_index;
   uint32_t data[4];
};
struct wclap_input_events {
   Pointer<void> ctx;
   Function<uint32_t,Pointer<const struct wclap_input_events> list> size;
   Function<Pointer<const wclap_event_header_t> ,Pointer<const struct wclap_input_events> list, uint32_t index> get;
};
struct wclap_output_events {
   Pointer<void> ctx;
   Function<bool,Pointer<const struct wclap_output_events> list,
                            Pointer<const wclap_event_header_t>       event> try_push;
};
struct wclap_audio_buffer {
   Pointer<Pointer<float>>  data32;
   Pointer<Pointer<double>> data64;
   uint32_t channel_count;
   uint32_t latency;
   uint64_t constant_mask;
};
typedef int32_t wclap_process_status;
struct wclap_process {
   int64_t steady_time;
   uint32_t frames_count;
   Pointer<const wclap_event_transport_t> transport;
   Pointer<const wclap_audio_buffer_t> audio_inputs;
   Pointer<wclap_audio_buffer_t>       audio_outputs;
   uint32_t                   audio_inputs_count;
   uint32_t                   audio_outputs_count;
   Pointer<const wclap_input_events_t>  in_events;
   Pointer<const wclap_output_events_t> out_events;
};
struct wclap_plugin_descriptor {
   wclap_version_t wclap_version;
   Pointer<const char> id;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> manual_url;
   Pointer<const char> support_url;
   Pointer<const char> version;
   Pointer<const char> description;
   Pointer<const char> Pointer<const> features;
};
struct wclap_plugin {
   Pointer<const wclap_plugin_descriptor_t> desc;

   Pointer<void> plugin_data;
   Function<bool,Pointer<const struct wclap_plugin> plugin> init;
   Function<void,Pointer<const struct wclap_plugin> plugin> destroy;
   Function<bool,Pointer<const struct wclap_plugin> plugin,
                            double                    sample_rate,
                            uint32_t                  min_frames_count,
                            uint32_t                  max_frames_count> activate;
   Function<void,Pointer<const struct wclap_plugin> plugin> deactivate;
   Function<bool,Pointer<const struct wclap_plugin> plugin> start_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> stop_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> reset;
   Function<wclap_process_status,Pointer<const struct wclap_plugin> plugin,
                                          Pointer<const wclap_process_t>     process> process;
   Function<Pointer<const void> ,Pointer<const struct wclap_plugin> plugin, Pointer<const char> id> get_extension;
   Function<void,Pointer<const struct wclap_plugin> plugin> on_main_thread;
};
typedef uint32_t wclap_posix_fd_flags_t;
struct wclap_plugin_posix_fd_support {
   Function<void,Pointer<const wclap_plugin_t> plugin, int fd, wclap_posix_fd_flags_t flags> on_fd;
};
struct wclap_host_posix_fd_support {
   Function<bool,Pointer<const wclap_host_t> host, int fd, wclap_posix_fd_flags_t flags> register_fd;
   Function<bool,Pointer<const wclap_host_t> host, int fd, wclap_posix_fd_flags_t flags> modify_fd;
   Function<bool,Pointer<const wclap_host_t> host, int fd> unregister_fd;
};
struct wclap_version {
   uint32_t major;
   uint32_t minor;
   uint32_t revision;
};
struct wclap_host {
   wclap_version_t wclap_version;

   Pointer<void> host_data;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> version;
   Function<Pointer<const void> ,Pointer<const struct wclap_host> host, Pointer<const char> extension_id> get_extension;
   Function<void,Pointer<const struct wclap_host> host> request_restart;
   Function<void,Pointer<const struct wclap_host> host> request_process;
   Function<void,Pointer<const struct wclap_host> host> request_callback;
};
typedef int64_t wclap_beattime;
typedef int64_t wclap_sectime;
typedef uint32_t wclap_id;
typedef int32_t wclap_note_expression;
struct wclap_event_header {
   uint32_t size;
   uint32_t time;
   uint16_t space_id;
   uint16_t type;
   uint32_t flags;
};
struct wclap_event_note {
   wclap_event_header_t header;

   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;
   double  velocity;
};
struct wclap_event_note_expression {
   wclap_event_header_t header;

   wclap_note_expression expression_id;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_value {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_mod {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double amount;
};
struct wclap_event_param_gesture {
   wclap_event_header_t header;
   wclap_id param_id;
};
struct wclap_event_transport {
   wclap_event_header_t header;

   uint32_t flags;

   wclap_beattime song_pos_beats;
   wclap_sectime  song_pos_seconds;

   double tempo;
   double tempo_inc;

   wclap_beattime loop_start_beats;
   wclap_beattime loop_end_beats;
   wclap_sectime  loop_start_seconds;
   wclap_sectime  loop_end_seconds;

   wclap_beattime bar_start;
   int32_t       bar_number;

   uint16_t tsig_num;
   uint16_t tsig_denom;
};
struct wclap_event_midi {
   wclap_event_header_t header;

   uint16_t port_index;
   uint8_t  data[3];
};
struct wclap_event_midi_sysex {
   wclap_event_header_t header;

   uint16_t       port_index;
   Pointer<const uint8_t> buffer;
   uint32_t       size;
};
struct wclap_event_midi2 {
   wclap_event_header_t header;

   uint16_t port_index;
   uint32_t data[4];
};
struct wclap_input_events {
   Pointer<void> ctx;
   Function<uint32_t,Pointer<const struct wclap_input_events> list> size;
   Function<Pointer<const wclap_event_header_t> ,Pointer<const struct wclap_input_events> list, uint32_t index> get;
};
struct wclap_output_events {
   Pointer<void> ctx;
   Function<bool,Pointer<const struct wclap_output_events> list,
                            Pointer<const wclap_event_header_t>       event> try_push;
};
struct wclap_audio_buffer {
   Pointer<Pointer<float>>  data32;
   Pointer<Pointer<double>> data64;
   uint32_t channel_count;
   uint32_t latency;
   uint64_t constant_mask;
};
typedef int32_t wclap_process_status;
struct wclap_process {
   int64_t steady_time;
   uint32_t frames_count;
   Pointer<const wclap_event_transport_t> transport;
   Pointer<const wclap_audio_buffer_t> audio_inputs;
   Pointer<wclap_audio_buffer_t>       audio_outputs;
   uint32_t                   audio_inputs_count;
   uint32_t                   audio_outputs_count;
   Pointer<const wclap_input_events_t>  in_events;
   Pointer<const wclap_output_events_t> out_events;
};
struct wclap_plugin_descriptor {
   wclap_version_t wclap_version;
   Pointer<const char> id;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> manual_url;
   Pointer<const char> support_url;
   Pointer<const char> version;
   Pointer<const char> description;
   Pointer<const char> Pointer<const> features;
};
struct wclap_plugin {
   Pointer<const wclap_plugin_descriptor_t> desc;

   Pointer<void> plugin_data;
   Function<bool,Pointer<const struct wclap_plugin> plugin> init;
   Function<void,Pointer<const struct wclap_plugin> plugin> destroy;
   Function<bool,Pointer<const struct wclap_plugin> plugin,
                            double                    sample_rate,
                            uint32_t                  min_frames_count,
                            uint32_t                  max_frames_count> activate;
   Function<void,Pointer<const struct wclap_plugin> plugin> deactivate;
   Function<bool,Pointer<const struct wclap_plugin> plugin> start_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> stop_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> reset;
   Function<wclap_process_status,Pointer<const struct wclap_plugin> plugin,
                                          Pointer<const wclap_process_t>     process> process;
   Function<Pointer<const void> ,Pointer<const struct wclap_plugin> plugin, Pointer<const char> id> get_extension;
   Function<void,Pointer<const struct wclap_plugin> plugin> on_main_thread;
};
struct wclap_plugin_preset_load {
   Function<bool,Pointer<const wclap_plugin_t> plugin,
                                 uint32_t             location_kind,
                                 Pointer<const char>          location,
                                 Pointer<const char>          load_key> from_location;
};
struct wclap_host_preset_load {
   Function<void,Pointer<const wclap_host_t> host,
                            uint32_t           location_kind,
                            Pointer<const char>        location,
                            Pointer<const char>        load_key,
                            int32_t            os_error,
                            Pointer<const char>        msg> on_error;
   Function<void,Pointer<const wclap_host_t> host,
                          uint32_t           location_kind,
                          Pointer<const char>        location,
                          Pointer<const char>        load_key> loaded;
};
struct wclap_version {
   uint32_t major;
   uint32_t minor;
   uint32_t revision;
};
struct wclap_host {
   wclap_version_t wclap_version;

   Pointer<void> host_data;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> version;
   Function<Pointer<const void> ,Pointer<const struct wclap_host> host, Pointer<const char> extension_id> get_extension;
   Function<void,Pointer<const struct wclap_host> host> request_restart;
   Function<void,Pointer<const struct wclap_host> host> request_process;
   Function<void,Pointer<const struct wclap_host> host> request_callback;
};
typedef int64_t wclap_beattime;
typedef int64_t wclap_sectime;
typedef uint32_t wclap_id;
typedef int32_t wclap_note_expression;
struct wclap_event_header {
   uint32_t size;
   uint32_t time;
   uint16_t space_id;
   uint16_t type;
   uint32_t flags;
};
struct wclap_event_note {
   wclap_event_header_t header;

   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;
   double  velocity;
};
struct wclap_event_note_expression {
   wclap_event_header_t header;

   wclap_note_expression expression_id;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_value {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_mod {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double amount;
};
struct wclap_event_param_gesture {
   wclap_event_header_t header;
   wclap_id param_id;
};
struct wclap_event_transport {
   wclap_event_header_t header;

   uint32_t flags;

   wclap_beattime song_pos_beats;
   wclap_sectime  song_pos_seconds;

   double tempo;
   double tempo_inc;

   wclap_beattime loop_start_beats;
   wclap_beattime loop_end_beats;
   wclap_sectime  loop_start_seconds;
   wclap_sectime  loop_end_seconds;

   wclap_beattime bar_start;
   int32_t       bar_number;

   uint16_t tsig_num;
   uint16_t tsig_denom;
};
struct wclap_event_midi {
   wclap_event_header_t header;

   uint16_t port_index;
   uint8_t  data[3];
};
struct wclap_event_midi_sysex {
   wclap_event_header_t header;

   uint16_t       port_index;
   Pointer<const uint8_t> buffer;
   uint32_t       size;
};
struct wclap_event_midi2 {
   wclap_event_header_t header;

   uint16_t port_index;
   uint32_t data[4];
};
struct wclap_input_events {
   Pointer<void> ctx;
   Function<uint32_t,Pointer<const struct wclap_input_events> list> size;
   Function<Pointer<const wclap_event_header_t> ,Pointer<const struct wclap_input_events> list, uint32_t index> get;
};
struct wclap_output_events {
   Pointer<void> ctx;
   Function<bool,Pointer<const struct wclap_output_events> list,
                            Pointer<const wclap_event_header_t>       event> try_push;
};
struct wclap_audio_buffer {
   Pointer<Pointer<float>>  data32;
   Pointer<Pointer<double>> data64;
   uint32_t channel_count;
   uint32_t latency;
   uint64_t constant_mask;
};
typedef int32_t wclap_process_status;
struct wclap_process {
   int64_t steady_time;
   uint32_t frames_count;
   Pointer<const wclap_event_transport_t> transport;
   Pointer<const wclap_audio_buffer_t> audio_inputs;
   Pointer<wclap_audio_buffer_t>       audio_outputs;
   uint32_t                   audio_inputs_count;
   uint32_t                   audio_outputs_count;
   Pointer<const wclap_input_events_t>  in_events;
   Pointer<const wclap_output_events_t> out_events;
};
struct wclap_plugin_descriptor {
   wclap_version_t wclap_version;
   Pointer<const char> id;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> manual_url;
   Pointer<const char> support_url;
   Pointer<const char> version;
   Pointer<const char> description;
   Pointer<const char> Pointer<const> features;
};
struct wclap_plugin {
   Pointer<const wclap_plugin_descriptor_t> desc;

   Pointer<void> plugin_data;
   Function<bool,Pointer<const struct wclap_plugin> plugin> init;
   Function<void,Pointer<const struct wclap_plugin> plugin> destroy;
   Function<bool,Pointer<const struct wclap_plugin> plugin,
                            double                    sample_rate,
                            uint32_t                  min_frames_count,
                            uint32_t                  max_frames_count> activate;
   Function<void,Pointer<const struct wclap_plugin> plugin> deactivate;
   Function<bool,Pointer<const struct wclap_plugin> plugin> start_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> stop_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> reset;
   Function<wclap_process_status,Pointer<const struct wclap_plugin> plugin,
                                          Pointer<const wclap_process_t>     process> process;
   Function<Pointer<const void> ,Pointer<const struct wclap_plugin> plugin, Pointer<const char> id> get_extension;
   Function<void,Pointer<const struct wclap_plugin> plugin> on_main_thread;
};
struct wclap_remote_controls_page {
   char    section_name[CLAP_NAME_SIZE];
   wclap_id page_id;
   char    page_name[CLAP_NAME_SIZE];
   wclap_id param_ids[CLAP_REMOTE_CONTROLS_COUNT];
   bool is_for_preset;
};
struct wclap_plugin_remote_controls {
   Function<uint32_t,Pointer<const wclap_plugin_t> plugin> count;
   Function<bool,Pointer<const wclap_plugin_t>         plugin,
                       uint32_t                     page_index,
                       Pointer<wclap_remote_controls_page_t> page> get;
};
struct wclap_host_remote_controls {
   Function<void,Pointer<const wclap_host_t> host> changed;
   Function<void,Pointer<const wclap_host_t> host, wclap_id page_id> suggest_page;
};
struct wclap_version {
   uint32_t major;
   uint32_t minor;
   uint32_t revision;
};
struct wclap_host {
   wclap_version_t wclap_version;

   Pointer<void> host_data;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> version;
   Function<Pointer<const void> ,Pointer<const struct wclap_host> host, Pointer<const char> extension_id> get_extension;
   Function<void,Pointer<const struct wclap_host> host> request_restart;
   Function<void,Pointer<const struct wclap_host> host> request_process;
   Function<void,Pointer<const struct wclap_host> host> request_callback;
};
typedef int64_t wclap_beattime;
typedef int64_t wclap_sectime;
typedef uint32_t wclap_id;
typedef int32_t wclap_note_expression;
struct wclap_event_header {
   uint32_t size;
   uint32_t time;
   uint16_t space_id;
   uint16_t type;
   uint32_t flags;
};
struct wclap_event_note {
   wclap_event_header_t header;

   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;
   double  velocity;
};
struct wclap_event_note_expression {
   wclap_event_header_t header;

   wclap_note_expression expression_id;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_value {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_mod {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double amount;
};
struct wclap_event_param_gesture {
   wclap_event_header_t header;
   wclap_id param_id;
};
struct wclap_event_transport {
   wclap_event_header_t header;

   uint32_t flags;

   wclap_beattime song_pos_beats;
   wclap_sectime  song_pos_seconds;

   double tempo;
   double tempo_inc;

   wclap_beattime loop_start_beats;
   wclap_beattime loop_end_beats;
   wclap_sectime  loop_start_seconds;
   wclap_sectime  loop_end_seconds;

   wclap_beattime bar_start;
   int32_t       bar_number;

   uint16_t tsig_num;
   uint16_t tsig_denom;
};
struct wclap_event_midi {
   wclap_event_header_t header;

   uint16_t port_index;
   uint8_t  data[3];
};
struct wclap_event_midi_sysex {
   wclap_event_header_t header;

   uint16_t       port_index;
   Pointer<const uint8_t> buffer;
   uint32_t       size;
};
struct wclap_event_midi2 {
   wclap_event_header_t header;

   uint16_t port_index;
   uint32_t data[4];
};
struct wclap_input_events {
   Pointer<void> ctx;
   Function<uint32_t,Pointer<const struct wclap_input_events> list> size;
   Function<Pointer<const wclap_event_header_t> ,Pointer<const struct wclap_input_events> list, uint32_t index> get;
};
struct wclap_output_events {
   Pointer<void> ctx;
   Function<bool,Pointer<const struct wclap_output_events> list,
                            Pointer<const wclap_event_header_t>       event> try_push;
};
struct wclap_audio_buffer {
   Pointer<Pointer<float>>  data32;
   Pointer<Pointer<double>> data64;
   uint32_t channel_count;
   uint32_t latency;
   uint64_t constant_mask;
};
typedef int32_t wclap_process_status;
struct wclap_process {
   int64_t steady_time;
   uint32_t frames_count;
   Pointer<const wclap_event_transport_t> transport;
   Pointer<const wclap_audio_buffer_t> audio_inputs;
   Pointer<wclap_audio_buffer_t>       audio_outputs;
   uint32_t                   audio_inputs_count;
   uint32_t                   audio_outputs_count;
   Pointer<const wclap_input_events_t>  in_events;
   Pointer<const wclap_output_events_t> out_events;
};
struct wclap_plugin_descriptor {
   wclap_version_t wclap_version;
   Pointer<const char> id;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> manual_url;
   Pointer<const char> support_url;
   Pointer<const char> version;
   Pointer<const char> description;
   Pointer<const char> Pointer<const> features;
};
struct wclap_plugin {
   Pointer<const wclap_plugin_descriptor_t> desc;

   Pointer<void> plugin_data;
   Function<bool,Pointer<const struct wclap_plugin> plugin> init;
   Function<void,Pointer<const struct wclap_plugin> plugin> destroy;
   Function<bool,Pointer<const struct wclap_plugin> plugin,
                            double                    sample_rate,
                            uint32_t                  min_frames_count,
                            uint32_t                  max_frames_count> activate;
   Function<void,Pointer<const struct wclap_plugin> plugin> deactivate;
   Function<bool,Pointer<const struct wclap_plugin> plugin> start_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> stop_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> reset;
   Function<wclap_process_status,Pointer<const struct wclap_plugin> plugin,
                                          Pointer<const wclap_process_t>     process> process;
   Function<Pointer<const void> ,Pointer<const struct wclap_plugin> plugin, Pointer<const char> id> get_extension;
   Function<void,Pointer<const struct wclap_plugin> plugin> on_main_thread;
};
typedef int32_t wclap_plugin_render_mode;
struct wclap_plugin_render {
   Function<bool,Pointer<const wclap_plugin_t> plugin> has_hard_realtime_requirement;
   Function<bool,Pointer<const wclap_plugin_t> plugin, wclap_plugin_render_mode mode> set;
};
struct wclap_version {
   uint32_t major;
   uint32_t minor;
   uint32_t revision;
};
struct wclap_host {
   wclap_version_t wclap_version;

   Pointer<void> host_data;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> version;
   Function<Pointer<const void> ,Pointer<const struct wclap_host> host, Pointer<const char> extension_id> get_extension;
   Function<void,Pointer<const struct wclap_host> host> request_restart;
   Function<void,Pointer<const struct wclap_host> host> request_process;
   Function<void,Pointer<const struct wclap_host> host> request_callback;
};
typedef int64_t wclap_beattime;
typedef int64_t wclap_sectime;
typedef uint32_t wclap_id;
typedef int32_t wclap_note_expression;
struct wclap_event_header {
   uint32_t size;
   uint32_t time;
   uint16_t space_id;
   uint16_t type;
   uint32_t flags;
};
struct wclap_event_note {
   wclap_event_header_t header;

   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;
   double  velocity;
};
struct wclap_event_note_expression {
   wclap_event_header_t header;

   wclap_note_expression expression_id;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_value {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_mod {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double amount;
};
struct wclap_event_param_gesture {
   wclap_event_header_t header;
   wclap_id param_id;
};
struct wclap_event_transport {
   wclap_event_header_t header;

   uint32_t flags;

   wclap_beattime song_pos_beats;
   wclap_sectime  song_pos_seconds;

   double tempo;
   double tempo_inc;

   wclap_beattime loop_start_beats;
   wclap_beattime loop_end_beats;
   wclap_sectime  loop_start_seconds;
   wclap_sectime  loop_end_seconds;

   wclap_beattime bar_start;
   int32_t       bar_number;

   uint16_t tsig_num;
   uint16_t tsig_denom;
};
struct wclap_event_midi {
   wclap_event_header_t header;

   uint16_t port_index;
   uint8_t  data[3];
};
struct wclap_event_midi_sysex {
   wclap_event_header_t header;

   uint16_t       port_index;
   Pointer<const uint8_t> buffer;
   uint32_t       size;
};
struct wclap_event_midi2 {
   wclap_event_header_t header;

   uint16_t port_index;
   uint32_t data[4];
};
struct wclap_input_events {
   Pointer<void> ctx;
   Function<uint32_t,Pointer<const struct wclap_input_events> list> size;
   Function<Pointer<const wclap_event_header_t> ,Pointer<const struct wclap_input_events> list, uint32_t index> get;
};
struct wclap_output_events {
   Pointer<void> ctx;
   Function<bool,Pointer<const struct wclap_output_events> list,
                            Pointer<const wclap_event_header_t>       event> try_push;
};
struct wclap_audio_buffer {
   Pointer<Pointer<float>>  data32;
   Pointer<Pointer<double>> data64;
   uint32_t channel_count;
   uint32_t latency;
   uint64_t constant_mask;
};
typedef int32_t wclap_process_status;
struct wclap_process {
   int64_t steady_time;
   uint32_t frames_count;
   Pointer<const wclap_event_transport_t> transport;
   Pointer<const wclap_audio_buffer_t> audio_inputs;
   Pointer<wclap_audio_buffer_t>       audio_outputs;
   uint32_t                   audio_inputs_count;
   uint32_t                   audio_outputs_count;
   Pointer<const wclap_input_events_t>  in_events;
   Pointer<const wclap_output_events_t> out_events;
};
struct wclap_plugin_descriptor {
   wclap_version_t wclap_version;
   Pointer<const char> id;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> manual_url;
   Pointer<const char> support_url;
   Pointer<const char> version;
   Pointer<const char> description;
   Pointer<const char> Pointer<const> features;
};
struct wclap_plugin {
   Pointer<const wclap_plugin_descriptor_t> desc;

   Pointer<void> plugin_data;
   Function<bool,Pointer<const struct wclap_plugin> plugin> init;
   Function<void,Pointer<const struct wclap_plugin> plugin> destroy;
   Function<bool,Pointer<const struct wclap_plugin> plugin,
                            double                    sample_rate,
                            uint32_t                  min_frames_count,
                            uint32_t                  max_frames_count> activate;
   Function<void,Pointer<const struct wclap_plugin> plugin> deactivate;
   Function<bool,Pointer<const struct wclap_plugin> plugin> start_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> stop_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> reset;
   Function<wclap_process_status,Pointer<const struct wclap_plugin> plugin,
                                          Pointer<const wclap_process_t>     process> process;
   Function<Pointer<const void> ,Pointer<const struct wclap_plugin> plugin, Pointer<const char> id> get_extension;
   Function<void,Pointer<const struct wclap_plugin> plugin> on_main_thread;
};
struct wclap_istream {
   Pointer<void> ctx;
   Function<int64_t,Pointer<const struct wclap_istream> stream, Pointer<void> buffer, uint64_t size> read;
};
struct wclap_ostream {
   Pointer<void> ctx;
   Function<int64_t,Pointer<const struct wclap_ostream> stream, Pointer<const void> buffer, uint64_t size> write;
};
struct wclap_plugin_state_context {
   Function<bool,Pointer<const wclap_plugin_t>  plugin,
                        Pointer<const wclap_ostream_t> stream,
                        uint32_t              context_type> save;
   Function<bool,Pointer<const wclap_plugin_t>  plugin,
                        Pointer<const wclap_istream_t> stream,
                        uint32_t              context_type> load;
};
struct wclap_version {
   uint32_t major;
   uint32_t minor;
   uint32_t revision;
};
struct wclap_host {
   wclap_version_t wclap_version;

   Pointer<void> host_data;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> version;
   Function<Pointer<const void> ,Pointer<const struct wclap_host> host, Pointer<const char> extension_id> get_extension;
   Function<void,Pointer<const struct wclap_host> host> request_restart;
   Function<void,Pointer<const struct wclap_host> host> request_process;
   Function<void,Pointer<const struct wclap_host> host> request_callback;
};
typedef int64_t wclap_beattime;
typedef int64_t wclap_sectime;
typedef uint32_t wclap_id;
typedef int32_t wclap_note_expression;
struct wclap_event_header {
   uint32_t size;
   uint32_t time;
   uint16_t space_id;
   uint16_t type;
   uint32_t flags;
};
struct wclap_event_note {
   wclap_event_header_t header;

   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;
   double  velocity;
};
struct wclap_event_note_expression {
   wclap_event_header_t header;

   wclap_note_expression expression_id;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_value {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_mod {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double amount;
};
struct wclap_event_param_gesture {
   wclap_event_header_t header;
   wclap_id param_id;
};
struct wclap_event_transport {
   wclap_event_header_t header;

   uint32_t flags;

   wclap_beattime song_pos_beats;
   wclap_sectime  song_pos_seconds;

   double tempo;
   double tempo_inc;

   wclap_beattime loop_start_beats;
   wclap_beattime loop_end_beats;
   wclap_sectime  loop_start_seconds;
   wclap_sectime  loop_end_seconds;

   wclap_beattime bar_start;
   int32_t       bar_number;

   uint16_t tsig_num;
   uint16_t tsig_denom;
};
struct wclap_event_midi {
   wclap_event_header_t header;

   uint16_t port_index;
   uint8_t  data[3];
};
struct wclap_event_midi_sysex {
   wclap_event_header_t header;

   uint16_t       port_index;
   Pointer<const uint8_t> buffer;
   uint32_t       size;
};
struct wclap_event_midi2 {
   wclap_event_header_t header;

   uint16_t port_index;
   uint32_t data[4];
};
struct wclap_input_events {
   Pointer<void> ctx;
   Function<uint32_t,Pointer<const struct wclap_input_events> list> size;
   Function<Pointer<const wclap_event_header_t> ,Pointer<const struct wclap_input_events> list, uint32_t index> get;
};
struct wclap_output_events {
   Pointer<void> ctx;
   Function<bool,Pointer<const struct wclap_output_events> list,
                            Pointer<const wclap_event_header_t>       event> try_push;
};
struct wclap_audio_buffer {
   Pointer<Pointer<float>>  data32;
   Pointer<Pointer<double>> data64;
   uint32_t channel_count;
   uint32_t latency;
   uint64_t constant_mask;
};
typedef int32_t wclap_process_status;
struct wclap_process {
   int64_t steady_time;
   uint32_t frames_count;
   Pointer<const wclap_event_transport_t> transport;
   Pointer<const wclap_audio_buffer_t> audio_inputs;
   Pointer<wclap_audio_buffer_t>       audio_outputs;
   uint32_t                   audio_inputs_count;
   uint32_t                   audio_outputs_count;
   Pointer<const wclap_input_events_t>  in_events;
   Pointer<const wclap_output_events_t> out_events;
};
struct wclap_plugin_descriptor {
   wclap_version_t wclap_version;
   Pointer<const char> id;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> manual_url;
   Pointer<const char> support_url;
   Pointer<const char> version;
   Pointer<const char> description;
   Pointer<const char> Pointer<const> features;
};
struct wclap_plugin {
   Pointer<const wclap_plugin_descriptor_t> desc;

   Pointer<void> plugin_data;
   Function<bool,Pointer<const struct wclap_plugin> plugin> init;
   Function<void,Pointer<const struct wclap_plugin> plugin> destroy;
   Function<bool,Pointer<const struct wclap_plugin> plugin,
                            double                    sample_rate,
                            uint32_t                  min_frames_count,
                            uint32_t                  max_frames_count> activate;
   Function<void,Pointer<const struct wclap_plugin> plugin> deactivate;
   Function<bool,Pointer<const struct wclap_plugin> plugin> start_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> stop_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> reset;
   Function<wclap_process_status,Pointer<const struct wclap_plugin> plugin,
                                          Pointer<const wclap_process_t>     process> process;
   Function<Pointer<const void> ,Pointer<const struct wclap_plugin> plugin, Pointer<const char> id> get_extension;
   Function<void,Pointer<const struct wclap_plugin> plugin> on_main_thread;
};
struct wclap_istream {
   Pointer<void> ctx;
   Function<int64_t,Pointer<const struct wclap_istream> stream, Pointer<void> buffer, uint64_t size> read;
};
struct wclap_ostream {
   Pointer<void> ctx;
   Function<int64_t,Pointer<const struct wclap_ostream> stream, Pointer<const void> buffer, uint64_t size> write;
};
struct wclap_plugin_state {
   Function<bool,Pointer<const wclap_plugin_t> plugin, Pointer<const wclap_ostream_t> stream> save;
   Function<bool,Pointer<const wclap_plugin_t> plugin, Pointer<const wclap_istream_t> stream> load;
};
struct wclap_host_state {
   Function<void,Pointer<const wclap_host_t> host> mark_dirty;
};
struct wclap_version {
   uint32_t major;
   uint32_t minor;
   uint32_t revision;
};
struct wclap_host {
   wclap_version_t wclap_version;

   Pointer<void> host_data;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> version;
   Function<Pointer<const void> ,Pointer<const struct wclap_host> host, Pointer<const char> extension_id> get_extension;
   Function<void,Pointer<const struct wclap_host> host> request_restart;
   Function<void,Pointer<const struct wclap_host> host> request_process;
   Function<void,Pointer<const struct wclap_host> host> request_callback;
};
typedef int64_t wclap_beattime;
typedef int64_t wclap_sectime;
typedef uint32_t wclap_id;
typedef int32_t wclap_note_expression;
struct wclap_event_header {
   uint32_t size;
   uint32_t time;
   uint16_t space_id;
   uint16_t type;
   uint32_t flags;
};
struct wclap_event_note {
   wclap_event_header_t header;

   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;
   double  velocity;
};
struct wclap_event_note_expression {
   wclap_event_header_t header;

   wclap_note_expression expression_id;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_value {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_mod {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double amount;
};
struct wclap_event_param_gesture {
   wclap_event_header_t header;
   wclap_id param_id;
};
struct wclap_event_transport {
   wclap_event_header_t header;

   uint32_t flags;

   wclap_beattime song_pos_beats;
   wclap_sectime  song_pos_seconds;

   double tempo;
   double tempo_inc;

   wclap_beattime loop_start_beats;
   wclap_beattime loop_end_beats;
   wclap_sectime  loop_start_seconds;
   wclap_sectime  loop_end_seconds;

   wclap_beattime bar_start;
   int32_t       bar_number;

   uint16_t tsig_num;
   uint16_t tsig_denom;
};
struct wclap_event_midi {
   wclap_event_header_t header;

   uint16_t port_index;
   uint8_t  data[3];
};
struct wclap_event_midi_sysex {
   wclap_event_header_t header;

   uint16_t       port_index;
   Pointer<const uint8_t> buffer;
   uint32_t       size;
};
struct wclap_event_midi2 {
   wclap_event_header_t header;

   uint16_t port_index;
   uint32_t data[4];
};
struct wclap_input_events {
   Pointer<void> ctx;
   Function<uint32_t,Pointer<const struct wclap_input_events> list> size;
   Function<Pointer<const wclap_event_header_t> ,Pointer<const struct wclap_input_events> list, uint32_t index> get;
};
struct wclap_output_events {
   Pointer<void> ctx;
   Function<bool,Pointer<const struct wclap_output_events> list,
                            Pointer<const wclap_event_header_t>       event> try_push;
};
struct wclap_audio_buffer {
   Pointer<Pointer<float>>  data32;
   Pointer<Pointer<double>> data64;
   uint32_t channel_count;
   uint32_t latency;
   uint64_t constant_mask;
};
typedef int32_t wclap_process_status;
struct wclap_process {
   int64_t steady_time;
   uint32_t frames_count;
   Pointer<const wclap_event_transport_t> transport;
   Pointer<const wclap_audio_buffer_t> audio_inputs;
   Pointer<wclap_audio_buffer_t>       audio_outputs;
   uint32_t                   audio_inputs_count;
   uint32_t                   audio_outputs_count;
   Pointer<const wclap_input_events_t>  in_events;
   Pointer<const wclap_output_events_t> out_events;
};
struct wclap_plugin_descriptor {
   wclap_version_t wclap_version;
   Pointer<const char> id;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> manual_url;
   Pointer<const char> support_url;
   Pointer<const char> version;
   Pointer<const char> description;
   Pointer<const char> Pointer<const> features;
};
struct wclap_plugin {
   Pointer<const wclap_plugin_descriptor_t> desc;

   Pointer<void> plugin_data;
   Function<bool,Pointer<const struct wclap_plugin> plugin> init;
   Function<void,Pointer<const struct wclap_plugin> plugin> destroy;
   Function<bool,Pointer<const struct wclap_plugin> plugin,
                            double                    sample_rate,
                            uint32_t                  min_frames_count,
                            uint32_t                  max_frames_count> activate;
   Function<void,Pointer<const struct wclap_plugin> plugin> deactivate;
   Function<bool,Pointer<const struct wclap_plugin> plugin> start_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> stop_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> reset;
   Function<wclap_process_status,Pointer<const struct wclap_plugin> plugin,
                                          Pointer<const wclap_process_t>     process> process;
   Function<Pointer<const void> ,Pointer<const struct wclap_plugin> plugin, Pointer<const char> id> get_extension;
   Function<void,Pointer<const struct wclap_plugin> plugin> on_main_thread;
};
struct wclap_plugin_surround {
   Function<bool,Pointer<const wclap_plugin_t> plugin, uint64_t channel_mask> is_channel_mask_supported;
   Function<uint32_t,Pointer<const wclap_plugin_t> plugin,
                                       bool                 is_input,
                                       uint32_t             port_index,
                                       Pointer<uint8_t>             channel_map,
                                       uint32_t             channel_map_capacity> get_channel_map;
};
struct wclap_host_surround {
   Function<void,Pointer<const wclap_host_t> host> changed;
};
struct wclap_version {
   uint32_t major;
   uint32_t minor;
   uint32_t revision;
};
struct wclap_host {
   wclap_version_t wclap_version;

   Pointer<void> host_data;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> version;
   Function<Pointer<const void> ,Pointer<const struct wclap_host> host, Pointer<const char> extension_id> get_extension;
   Function<void,Pointer<const struct wclap_host> host> request_restart;
   Function<void,Pointer<const struct wclap_host> host> request_process;
   Function<void,Pointer<const struct wclap_host> host> request_callback;
};
typedef int64_t wclap_beattime;
typedef int64_t wclap_sectime;
typedef uint32_t wclap_id;
typedef int32_t wclap_note_expression;
struct wclap_event_header {
   uint32_t size;
   uint32_t time;
   uint16_t space_id;
   uint16_t type;
   uint32_t flags;
};
struct wclap_event_note {
   wclap_event_header_t header;

   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;
   double  velocity;
};
struct wclap_event_note_expression {
   wclap_event_header_t header;

   wclap_note_expression expression_id;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_value {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_mod {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double amount;
};
struct wclap_event_param_gesture {
   wclap_event_header_t header;
   wclap_id param_id;
};
struct wclap_event_transport {
   wclap_event_header_t header;

   uint32_t flags;

   wclap_beattime song_pos_beats;
   wclap_sectime  song_pos_seconds;

   double tempo;
   double tempo_inc;

   wclap_beattime loop_start_beats;
   wclap_beattime loop_end_beats;
   wclap_sectime  loop_start_seconds;
   wclap_sectime  loop_end_seconds;

   wclap_beattime bar_start;
   int32_t       bar_number;

   uint16_t tsig_num;
   uint16_t tsig_denom;
};
struct wclap_event_midi {
   wclap_event_header_t header;

   uint16_t port_index;
   uint8_t  data[3];
};
struct wclap_event_midi_sysex {
   wclap_event_header_t header;

   uint16_t       port_index;
   Pointer<const uint8_t> buffer;
   uint32_t       size;
};
struct wclap_event_midi2 {
   wclap_event_header_t header;

   uint16_t port_index;
   uint32_t data[4];
};
struct wclap_input_events {
   Pointer<void> ctx;
   Function<uint32_t,Pointer<const struct wclap_input_events> list> size;
   Function<Pointer<const wclap_event_header_t> ,Pointer<const struct wclap_input_events> list, uint32_t index> get;
};
struct wclap_output_events {
   Pointer<void> ctx;
   Function<bool,Pointer<const struct wclap_output_events> list,
                            Pointer<const wclap_event_header_t>       event> try_push;
};
struct wclap_audio_buffer {
   Pointer<Pointer<float>>  data32;
   Pointer<Pointer<double>> data64;
   uint32_t channel_count;
   uint32_t latency;
   uint64_t constant_mask;
};
typedef int32_t wclap_process_status;
struct wclap_process {
   int64_t steady_time;
   uint32_t frames_count;
   Pointer<const wclap_event_transport_t> transport;
   Pointer<const wclap_audio_buffer_t> audio_inputs;
   Pointer<wclap_audio_buffer_t>       audio_outputs;
   uint32_t                   audio_inputs_count;
   uint32_t                   audio_outputs_count;
   Pointer<const wclap_input_events_t>  in_events;
   Pointer<const wclap_output_events_t> out_events;
};
struct wclap_plugin_descriptor {
   wclap_version_t wclap_version;
   Pointer<const char> id;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> manual_url;
   Pointer<const char> support_url;
   Pointer<const char> version;
   Pointer<const char> description;
   Pointer<const char> Pointer<const> features;
};
struct wclap_plugin {
   Pointer<const wclap_plugin_descriptor_t> desc;

   Pointer<void> plugin_data;
   Function<bool,Pointer<const struct wclap_plugin> plugin> init;
   Function<void,Pointer<const struct wclap_plugin> plugin> destroy;
   Function<bool,Pointer<const struct wclap_plugin> plugin,
                            double                    sample_rate,
                            uint32_t                  min_frames_count,
                            uint32_t                  max_frames_count> activate;
   Function<void,Pointer<const struct wclap_plugin> plugin> deactivate;
   Function<bool,Pointer<const struct wclap_plugin> plugin> start_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> stop_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> reset;
   Function<wclap_process_status,Pointer<const struct wclap_plugin> plugin,
                                          Pointer<const wclap_process_t>     process> process;
   Function<Pointer<const void> ,Pointer<const struct wclap_plugin> plugin, Pointer<const char> id> get_extension;
   Function<void,Pointer<const struct wclap_plugin> plugin> on_main_thread;
};
struct wclap_plugin_tail {
   Function<uint32_t,Pointer<const wclap_plugin_t> plugin> get;
};
struct wclap_host_tail {
   Function<void,Pointer<const wclap_host_t> host> changed;
};
struct wclap_version {
   uint32_t major;
   uint32_t minor;
   uint32_t revision;
};
struct wclap_host {
   wclap_version_t wclap_version;

   Pointer<void> host_data;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> version;
   Function<Pointer<const void> ,Pointer<const struct wclap_host> host, Pointer<const char> extension_id> get_extension;
   Function<void,Pointer<const struct wclap_host> host> request_restart;
   Function<void,Pointer<const struct wclap_host> host> request_process;
   Function<void,Pointer<const struct wclap_host> host> request_callback;
};
typedef int64_t wclap_beattime;
typedef int64_t wclap_sectime;
typedef uint32_t wclap_id;
typedef int32_t wclap_note_expression;
struct wclap_event_header {
   uint32_t size;
   uint32_t time;
   uint16_t space_id;
   uint16_t type;
   uint32_t flags;
};
struct wclap_event_note {
   wclap_event_header_t header;

   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;
   double  velocity;
};
struct wclap_event_note_expression {
   wclap_event_header_t header;

   wclap_note_expression expression_id;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_value {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_mod {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double amount;
};
struct wclap_event_param_gesture {
   wclap_event_header_t header;
   wclap_id param_id;
};
struct wclap_event_transport {
   wclap_event_header_t header;

   uint32_t flags;

   wclap_beattime song_pos_beats;
   wclap_sectime  song_pos_seconds;

   double tempo;
   double tempo_inc;

   wclap_beattime loop_start_beats;
   wclap_beattime loop_end_beats;
   wclap_sectime  loop_start_seconds;
   wclap_sectime  loop_end_seconds;

   wclap_beattime bar_start;
   int32_t       bar_number;

   uint16_t tsig_num;
   uint16_t tsig_denom;
};
struct wclap_event_midi {
   wclap_event_header_t header;

   uint16_t port_index;
   uint8_t  data[3];
};
struct wclap_event_midi_sysex {
   wclap_event_header_t header;

   uint16_t       port_index;
   Pointer<const uint8_t> buffer;
   uint32_t       size;
};
struct wclap_event_midi2 {
   wclap_event_header_t header;

   uint16_t port_index;
   uint32_t data[4];
};
struct wclap_input_events {
   Pointer<void> ctx;
   Function<uint32_t,Pointer<const struct wclap_input_events> list> size;
   Function<Pointer<const wclap_event_header_t> ,Pointer<const struct wclap_input_events> list, uint32_t index> get;
};
struct wclap_output_events {
   Pointer<void> ctx;
   Function<bool,Pointer<const struct wclap_output_events> list,
                            Pointer<const wclap_event_header_t>       event> try_push;
};
struct wclap_audio_buffer {
   Pointer<Pointer<float>>  data32;
   Pointer<Pointer<double>> data64;
   uint32_t channel_count;
   uint32_t latency;
   uint64_t constant_mask;
};
typedef int32_t wclap_process_status;
struct wclap_process {
   int64_t steady_time;
   uint32_t frames_count;
   Pointer<const wclap_event_transport_t> transport;
   Pointer<const wclap_audio_buffer_t> audio_inputs;
   Pointer<wclap_audio_buffer_t>       audio_outputs;
   uint32_t                   audio_inputs_count;
   uint32_t                   audio_outputs_count;
   Pointer<const wclap_input_events_t>  in_events;
   Pointer<const wclap_output_events_t> out_events;
};
struct wclap_plugin_descriptor {
   wclap_version_t wclap_version;
   Pointer<const char> id;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> manual_url;
   Pointer<const char> support_url;
   Pointer<const char> version;
   Pointer<const char> description;
   Pointer<const char> Pointer<const> features;
};
struct wclap_plugin {
   Pointer<const wclap_plugin_descriptor_t> desc;

   Pointer<void> plugin_data;
   Function<bool,Pointer<const struct wclap_plugin> plugin> init;
   Function<void,Pointer<const struct wclap_plugin> plugin> destroy;
   Function<bool,Pointer<const struct wclap_plugin> plugin,
                            double                    sample_rate,
                            uint32_t                  min_frames_count,
                            uint32_t                  max_frames_count> activate;
   Function<void,Pointer<const struct wclap_plugin> plugin> deactivate;
   Function<bool,Pointer<const struct wclap_plugin> plugin> start_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> stop_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> reset;
   Function<wclap_process_status,Pointer<const struct wclap_plugin> plugin,
                                          Pointer<const wclap_process_t>     process> process;
   Function<Pointer<const void> ,Pointer<const struct wclap_plugin> plugin, Pointer<const char> id> get_extension;
   Function<void,Pointer<const struct wclap_plugin> plugin> on_main_thread;
};
struct wclap_host_thread_check {
   Function<bool,Pointer<const wclap_host_t> host> is_main_thread;
   Function<bool,Pointer<const wclap_host_t> host> is_audio_thread;
};
struct wclap_version {
   uint32_t major;
   uint32_t minor;
   uint32_t revision;
};
struct wclap_host {
   wclap_version_t wclap_version;

   Pointer<void> host_data;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> version;
   Function<Pointer<const void> ,Pointer<const struct wclap_host> host, Pointer<const char> extension_id> get_extension;
   Function<void,Pointer<const struct wclap_host> host> request_restart;
   Function<void,Pointer<const struct wclap_host> host> request_process;
   Function<void,Pointer<const struct wclap_host> host> request_callback;
};
typedef int64_t wclap_beattime;
typedef int64_t wclap_sectime;
typedef uint32_t wclap_id;
typedef int32_t wclap_note_expression;
struct wclap_event_header {
   uint32_t size;
   uint32_t time;
   uint16_t space_id;
   uint16_t type;
   uint32_t flags;
};
struct wclap_event_note {
   wclap_event_header_t header;

   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;
   double  velocity;
};
struct wclap_event_note_expression {
   wclap_event_header_t header;

   wclap_note_expression expression_id;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_value {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_mod {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double amount;
};
struct wclap_event_param_gesture {
   wclap_event_header_t header;
   wclap_id param_id;
};
struct wclap_event_transport {
   wclap_event_header_t header;

   uint32_t flags;

   wclap_beattime song_pos_beats;
   wclap_sectime  song_pos_seconds;

   double tempo;
   double tempo_inc;

   wclap_beattime loop_start_beats;
   wclap_beattime loop_end_beats;
   wclap_sectime  loop_start_seconds;
   wclap_sectime  loop_end_seconds;

   wclap_beattime bar_start;
   int32_t       bar_number;

   uint16_t tsig_num;
   uint16_t tsig_denom;
};
struct wclap_event_midi {
   wclap_event_header_t header;

   uint16_t port_index;
   uint8_t  data[3];
};
struct wclap_event_midi_sysex {
   wclap_event_header_t header;

   uint16_t       port_index;
   Pointer<const uint8_t> buffer;
   uint32_t       size;
};
struct wclap_event_midi2 {
   wclap_event_header_t header;

   uint16_t port_index;
   uint32_t data[4];
};
struct wclap_input_events {
   Pointer<void> ctx;
   Function<uint32_t,Pointer<const struct wclap_input_events> list> size;
   Function<Pointer<const wclap_event_header_t> ,Pointer<const struct wclap_input_events> list, uint32_t index> get;
};
struct wclap_output_events {
   Pointer<void> ctx;
   Function<bool,Pointer<const struct wclap_output_events> list,
                            Pointer<const wclap_event_header_t>       event> try_push;
};
struct wclap_audio_buffer {
   Pointer<Pointer<float>>  data32;
   Pointer<Pointer<double>> data64;
   uint32_t channel_count;
   uint32_t latency;
   uint64_t constant_mask;
};
typedef int32_t wclap_process_status;
struct wclap_process {
   int64_t steady_time;
   uint32_t frames_count;
   Pointer<const wclap_event_transport_t> transport;
   Pointer<const wclap_audio_buffer_t> audio_inputs;
   Pointer<wclap_audio_buffer_t>       audio_outputs;
   uint32_t                   audio_inputs_count;
   uint32_t                   audio_outputs_count;
   Pointer<const wclap_input_events_t>  in_events;
   Pointer<const wclap_output_events_t> out_events;
};
struct wclap_plugin_descriptor {
   wclap_version_t wclap_version;
   Pointer<const char> id;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> manual_url;
   Pointer<const char> support_url;
   Pointer<const char> version;
   Pointer<const char> description;
   Pointer<const char> Pointer<const> features;
};
struct wclap_plugin {
   Pointer<const wclap_plugin_descriptor_t> desc;

   Pointer<void> plugin_data;
   Function<bool,Pointer<const struct wclap_plugin> plugin> init;
   Function<void,Pointer<const struct wclap_plugin> plugin> destroy;
   Function<bool,Pointer<const struct wclap_plugin> plugin,
                            double                    sample_rate,
                            uint32_t                  min_frames_count,
                            uint32_t                  max_frames_count> activate;
   Function<void,Pointer<const struct wclap_plugin> plugin> deactivate;
   Function<bool,Pointer<const struct wclap_plugin> plugin> start_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> stop_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> reset;
   Function<wclap_process_status,Pointer<const struct wclap_plugin> plugin,
                                          Pointer<const wclap_process_t>     process> process;
   Function<Pointer<const void> ,Pointer<const struct wclap_plugin> plugin, Pointer<const char> id> get_extension;
   Function<void,Pointer<const struct wclap_plugin> plugin> on_main_thread;
};
struct wclap_plugin_thread_pool {
   Function<void,Pointer<const wclap_plugin_t> plugin, uint32_t task_index> exec;
};
struct wclap_host_thread_pool {
   Function<bool,Pointer<const wclap_host_t> host, uint32_t num_tasks> request_exec;
};
struct wclap_version {
   uint32_t major;
   uint32_t minor;
   uint32_t revision;
};
struct wclap_host {
   wclap_version_t wclap_version;

   Pointer<void> host_data;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> version;
   Function<Pointer<const void> ,Pointer<const struct wclap_host> host, Pointer<const char> extension_id> get_extension;
   Function<void,Pointer<const struct wclap_host> host> request_restart;
   Function<void,Pointer<const struct wclap_host> host> request_process;
   Function<void,Pointer<const struct wclap_host> host> request_callback;
};
typedef int64_t wclap_beattime;
typedef int64_t wclap_sectime;
typedef uint32_t wclap_id;
typedef int32_t wclap_note_expression;
struct wclap_event_header {
   uint32_t size;
   uint32_t time;
   uint16_t space_id;
   uint16_t type;
   uint32_t flags;
};
struct wclap_event_note {
   wclap_event_header_t header;

   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;
   double  velocity;
};
struct wclap_event_note_expression {
   wclap_event_header_t header;

   wclap_note_expression expression_id;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_value {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_mod {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double amount;
};
struct wclap_event_param_gesture {
   wclap_event_header_t header;
   wclap_id param_id;
};
struct wclap_event_transport {
   wclap_event_header_t header;

   uint32_t flags;

   wclap_beattime song_pos_beats;
   wclap_sectime  song_pos_seconds;

   double tempo;
   double tempo_inc;

   wclap_beattime loop_start_beats;
   wclap_beattime loop_end_beats;
   wclap_sectime  loop_start_seconds;
   wclap_sectime  loop_end_seconds;

   wclap_beattime bar_start;
   int32_t       bar_number;

   uint16_t tsig_num;
   uint16_t tsig_denom;
};
struct wclap_event_midi {
   wclap_event_header_t header;

   uint16_t port_index;
   uint8_t  data[3];
};
struct wclap_event_midi_sysex {
   wclap_event_header_t header;

   uint16_t       port_index;
   Pointer<const uint8_t> buffer;
   uint32_t       size;
};
struct wclap_event_midi2 {
   wclap_event_header_t header;

   uint16_t port_index;
   uint32_t data[4];
};
struct wclap_input_events {
   Pointer<void> ctx;
   Function<uint32_t,Pointer<const struct wclap_input_events> list> size;
   Function<Pointer<const wclap_event_header_t> ,Pointer<const struct wclap_input_events> list, uint32_t index> get;
};
struct wclap_output_events {
   Pointer<void> ctx;
   Function<bool,Pointer<const struct wclap_output_events> list,
                            Pointer<const wclap_event_header_t>       event> try_push;
};
struct wclap_audio_buffer {
   Pointer<Pointer<float>>  data32;
   Pointer<Pointer<double>> data64;
   uint32_t channel_count;
   uint32_t latency;
   uint64_t constant_mask;
};
typedef int32_t wclap_process_status;
struct wclap_process {
   int64_t steady_time;
   uint32_t frames_count;
   Pointer<const wclap_event_transport_t> transport;
   Pointer<const wclap_audio_buffer_t> audio_inputs;
   Pointer<wclap_audio_buffer_t>       audio_outputs;
   uint32_t                   audio_inputs_count;
   uint32_t                   audio_outputs_count;
   Pointer<const wclap_input_events_t>  in_events;
   Pointer<const wclap_output_events_t> out_events;
};
struct wclap_plugin_descriptor {
   wclap_version_t wclap_version;
   Pointer<const char> id;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> manual_url;
   Pointer<const char> support_url;
   Pointer<const char> version;
   Pointer<const char> description;
   Pointer<const char> Pointer<const> features;
};
struct wclap_plugin {
   Pointer<const wclap_plugin_descriptor_t> desc;

   Pointer<void> plugin_data;
   Function<bool,Pointer<const struct wclap_plugin> plugin> init;
   Function<void,Pointer<const struct wclap_plugin> plugin> destroy;
   Function<bool,Pointer<const struct wclap_plugin> plugin,
                            double                    sample_rate,
                            uint32_t                  min_frames_count,
                            uint32_t                  max_frames_count> activate;
   Function<void,Pointer<const struct wclap_plugin> plugin> deactivate;
   Function<bool,Pointer<const struct wclap_plugin> plugin> start_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> stop_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> reset;
   Function<wclap_process_status,Pointer<const struct wclap_plugin> plugin,
                                          Pointer<const wclap_process_t>     process> process;
   Function<Pointer<const void> ,Pointer<const struct wclap_plugin> plugin, Pointer<const char> id> get_extension;
   Function<void,Pointer<const struct wclap_plugin> plugin> on_main_thread;
};
struct wclap_plugin_timer_support {
   Function<void,Pointer<const wclap_plugin_t> plugin, wclap_id timer_id> on_timer;
};
struct wclap_host_timer_support {
   Function<bool,Pointer<const wclap_host_t> host, uint32_t period_ms, Pointer<wclap_id> timer_id> register_timer;
   Function<bool,Pointer<const wclap_host_t> host, wclap_id timer_id> unregister_timer;
};
struct wclap_version {
   uint32_t major;
   uint32_t minor;
   uint32_t revision;
};
struct wclap_host {
   wclap_version_t wclap_version;

   Pointer<void> host_data;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> version;
   Function<Pointer<const void> ,Pointer<const struct wclap_host> host, Pointer<const char> extension_id> get_extension;
   Function<void,Pointer<const struct wclap_host> host> request_restart;
   Function<void,Pointer<const struct wclap_host> host> request_process;
   Function<void,Pointer<const struct wclap_host> host> request_callback;
};
typedef int64_t wclap_beattime;
typedef int64_t wclap_sectime;
typedef uint32_t wclap_id;
typedef int32_t wclap_note_expression;
struct wclap_event_header {
   uint32_t size;
   uint32_t time;
   uint16_t space_id;
   uint16_t type;
   uint32_t flags;
};
struct wclap_event_note {
   wclap_event_header_t header;

   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;
   double  velocity;
};
struct wclap_event_note_expression {
   wclap_event_header_t header;

   wclap_note_expression expression_id;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_value {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_mod {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double amount;
};
struct wclap_event_param_gesture {
   wclap_event_header_t header;
   wclap_id param_id;
};
struct wclap_event_transport {
   wclap_event_header_t header;

   uint32_t flags;

   wclap_beattime song_pos_beats;
   wclap_sectime  song_pos_seconds;

   double tempo;
   double tempo_inc;

   wclap_beattime loop_start_beats;
   wclap_beattime loop_end_beats;
   wclap_sectime  loop_start_seconds;
   wclap_sectime  loop_end_seconds;

   wclap_beattime bar_start;
   int32_t       bar_number;

   uint16_t tsig_num;
   uint16_t tsig_denom;
};
struct wclap_event_midi {
   wclap_event_header_t header;

   uint16_t port_index;
   uint8_t  data[3];
};
struct wclap_event_midi_sysex {
   wclap_event_header_t header;

   uint16_t       port_index;
   Pointer<const uint8_t> buffer;
   uint32_t       size;
};
struct wclap_event_midi2 {
   wclap_event_header_t header;

   uint16_t port_index;
   uint32_t data[4];
};
struct wclap_input_events {
   Pointer<void> ctx;
   Function<uint32_t,Pointer<const struct wclap_input_events> list> size;
   Function<Pointer<const wclap_event_header_t> ,Pointer<const struct wclap_input_events> list, uint32_t index> get;
};
struct wclap_output_events {
   Pointer<void> ctx;
   Function<bool,Pointer<const struct wclap_output_events> list,
                            Pointer<const wclap_event_header_t>       event> try_push;
};
struct wclap_audio_buffer {
   Pointer<Pointer<float>>  data32;
   Pointer<Pointer<double>> data64;
   uint32_t channel_count;
   uint32_t latency;
   uint64_t constant_mask;
};
typedef int32_t wclap_process_status;
struct wclap_process {
   int64_t steady_time;
   uint32_t frames_count;
   Pointer<const wclap_event_transport_t> transport;
   Pointer<const wclap_audio_buffer_t> audio_inputs;
   Pointer<wclap_audio_buffer_t>       audio_outputs;
   uint32_t                   audio_inputs_count;
   uint32_t                   audio_outputs_count;
   Pointer<const wclap_input_events_t>  in_events;
   Pointer<const wclap_output_events_t> out_events;
};
struct wclap_plugin_descriptor {
   wclap_version_t wclap_version;
   Pointer<const char> id;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> manual_url;
   Pointer<const char> support_url;
   Pointer<const char> version;
   Pointer<const char> description;
   Pointer<const char> Pointer<const> features;
};
struct wclap_plugin {
   Pointer<const wclap_plugin_descriptor_t> desc;

   Pointer<void> plugin_data;
   Function<bool,Pointer<const struct wclap_plugin> plugin> init;
   Function<void,Pointer<const struct wclap_plugin> plugin> destroy;
   Function<bool,Pointer<const struct wclap_plugin> plugin,
                            double                    sample_rate,
                            uint32_t                  min_frames_count,
                            uint32_t                  max_frames_count> activate;
   Function<void,Pointer<const struct wclap_plugin> plugin> deactivate;
   Function<bool,Pointer<const struct wclap_plugin> plugin> start_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> stop_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> reset;
   Function<wclap_process_status,Pointer<const struct wclap_plugin> plugin,
                                          Pointer<const wclap_process_t>     process> process;
   Function<Pointer<const void> ,Pointer<const struct wclap_plugin> plugin, Pointer<const char> id> get_extension;
   Function<void,Pointer<const struct wclap_plugin> plugin> on_main_thread;
};
struct wclap_color {
   uint8_t alpha;
   uint8_t red;
   uint8_t green;
   uint8_t blue;
};
struct wclap_track_info {
   uint64_t flags;
   char name[CLAP_NAME_SIZE];
   wclap_color_t color;
   int32_t     audio_channel_count;
   Pointer<const char> audio_port_type;
};
struct wclap_plugin_track_info {
   Function<void,Pointer<const wclap_plugin_t> plugin> changed;
};
struct wclap_host_track_info {
   Function<bool,Pointer<const wclap_host_t> host, Pointer<wclap_track_info_t> info> get;
};
struct wclap_version {
   uint32_t major;
   uint32_t minor;
   uint32_t revision;
};
struct wclap_host {
   wclap_version_t wclap_version;

   Pointer<void> host_data;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> version;
   Function<Pointer<const void> ,Pointer<const struct wclap_host> host, Pointer<const char> extension_id> get_extension;
   Function<void,Pointer<const struct wclap_host> host> request_restart;
   Function<void,Pointer<const struct wclap_host> host> request_process;
   Function<void,Pointer<const struct wclap_host> host> request_callback;
};
typedef int64_t wclap_beattime;
typedef int64_t wclap_sectime;
typedef uint32_t wclap_id;
typedef int32_t wclap_note_expression;
struct wclap_event_header {
   uint32_t size;
   uint32_t time;
   uint16_t space_id;
   uint16_t type;
   uint32_t flags;
};
struct wclap_event_note {
   wclap_event_header_t header;

   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;
   double  velocity;
};
struct wclap_event_note_expression {
   wclap_event_header_t header;

   wclap_note_expression expression_id;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_value {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_mod {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double amount;
};
struct wclap_event_param_gesture {
   wclap_event_header_t header;
   wclap_id param_id;
};
struct wclap_event_transport {
   wclap_event_header_t header;

   uint32_t flags;

   wclap_beattime song_pos_beats;
   wclap_sectime  song_pos_seconds;

   double tempo;
   double tempo_inc;

   wclap_beattime loop_start_beats;
   wclap_beattime loop_end_beats;
   wclap_sectime  loop_start_seconds;
   wclap_sectime  loop_end_seconds;

   wclap_beattime bar_start;
   int32_t       bar_number;

   uint16_t tsig_num;
   uint16_t tsig_denom;
};
struct wclap_event_midi {
   wclap_event_header_t header;

   uint16_t port_index;
   uint8_t  data[3];
};
struct wclap_event_midi_sysex {
   wclap_event_header_t header;

   uint16_t       port_index;
   Pointer<const uint8_t> buffer;
   uint32_t       size;
};
struct wclap_event_midi2 {
   wclap_event_header_t header;

   uint16_t port_index;
   uint32_t data[4];
};
struct wclap_input_events {
   Pointer<void> ctx;
   Function<uint32_t,Pointer<const struct wclap_input_events> list> size;
   Function<Pointer<const wclap_event_header_t> ,Pointer<const struct wclap_input_events> list, uint32_t index> get;
};
struct wclap_output_events {
   Pointer<void> ctx;
   Function<bool,Pointer<const struct wclap_output_events> list,
                            Pointer<const wclap_event_header_t>       event> try_push;
};
struct wclap_audio_buffer {
   Pointer<Pointer<float>>  data32;
   Pointer<Pointer<double>> data64;
   uint32_t channel_count;
   uint32_t latency;
   uint64_t constant_mask;
};
typedef int32_t wclap_process_status;
struct wclap_process {
   int64_t steady_time;
   uint32_t frames_count;
   Pointer<const wclap_event_transport_t> transport;
   Pointer<const wclap_audio_buffer_t> audio_inputs;
   Pointer<wclap_audio_buffer_t>       audio_outputs;
   uint32_t                   audio_inputs_count;
   uint32_t                   audio_outputs_count;
   Pointer<const wclap_input_events_t>  in_events;
   Pointer<const wclap_output_events_t> out_events;
};
struct wclap_plugin_descriptor {
   wclap_version_t wclap_version;
   Pointer<const char> id;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> manual_url;
   Pointer<const char> support_url;
   Pointer<const char> version;
   Pointer<const char> description;
   Pointer<const char> Pointer<const> features;
};
struct wclap_plugin {
   Pointer<const wclap_plugin_descriptor_t> desc;

   Pointer<void> plugin_data;
   Function<bool,Pointer<const struct wclap_plugin> plugin> init;
   Function<void,Pointer<const struct wclap_plugin> plugin> destroy;
   Function<bool,Pointer<const struct wclap_plugin> plugin,
                            double                    sample_rate,
                            uint32_t                  min_frames_count,
                            uint32_t                  max_frames_count> activate;
   Function<void,Pointer<const struct wclap_plugin> plugin> deactivate;
   Function<bool,Pointer<const struct wclap_plugin> plugin> start_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> stop_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> reset;
   Function<wclap_process_status,Pointer<const struct wclap_plugin> plugin,
                                          Pointer<const wclap_process_t>     process> process;
   Function<Pointer<const void> ,Pointer<const struct wclap_plugin> plugin, Pointer<const char> id> get_extension;
   Function<void,Pointer<const struct wclap_plugin> plugin> on_main_thread;
};
struct wclap_voice_info {
   uint32_t voice_count;
   uint32_t voice_capacity;

   uint64_t flags;
};
struct wclap_plugin_voice_info {
   Function<bool,Pointer<const wclap_plugin_t> plugin, Pointer<wclap_voice_info_t> info> get;
};
struct wclap_host_voice_info {
   Function<void,Pointer<const wclap_host_t> host> changed;
};
struct wclap_version {
   uint32_t major;
   uint32_t minor;
   uint32_t revision;
};
struct wclap_host {
   wclap_version_t wclap_version;

   Pointer<void> host_data;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> version;
   Function<Pointer<const void> ,Pointer<const struct wclap_host> host, Pointer<const char> extension_id> get_extension;
   Function<void,Pointer<const struct wclap_host> host> request_restart;
   Function<void,Pointer<const struct wclap_host> host> request_process;
   Function<void,Pointer<const struct wclap_host> host> request_callback;
};
typedef int64_t wclap_beattime;
typedef int64_t wclap_sectime;
typedef uint32_t wclap_id;
typedef int32_t wclap_note_expression;
struct wclap_event_header {
   uint32_t size;
   uint32_t time;
   uint16_t space_id;
   uint16_t type;
   uint32_t flags;
};
struct wclap_event_note {
   wclap_event_header_t header;

   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;
   double  velocity;
};
struct wclap_event_note_expression {
   wclap_event_header_t header;

   wclap_note_expression expression_id;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_value {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_mod {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double amount;
};
struct wclap_event_param_gesture {
   wclap_event_header_t header;
   wclap_id param_id;
};
struct wclap_event_transport {
   wclap_event_header_t header;

   uint32_t flags;

   wclap_beattime song_pos_beats;
   wclap_sectime  song_pos_seconds;

   double tempo;
   double tempo_inc;

   wclap_beattime loop_start_beats;
   wclap_beattime loop_end_beats;
   wclap_sectime  loop_start_seconds;
   wclap_sectime  loop_end_seconds;

   wclap_beattime bar_start;
   int32_t       bar_number;

   uint16_t tsig_num;
   uint16_t tsig_denom;
};
struct wclap_event_midi {
   wclap_event_header_t header;

   uint16_t port_index;
   uint8_t  data[3];
};
struct wclap_event_midi_sysex {
   wclap_event_header_t header;

   uint16_t       port_index;
   Pointer<const uint8_t> buffer;
   uint32_t       size;
};
struct wclap_event_midi2 {
   wclap_event_header_t header;

   uint16_t port_index;
   uint32_t data[4];
};
struct wclap_input_events {
   Pointer<void> ctx;
   Function<uint32_t,Pointer<const struct wclap_input_events> list> size;
   Function<Pointer<const wclap_event_header_t> ,Pointer<const struct wclap_input_events> list, uint32_t index> get;
};
struct wclap_output_events {
   Pointer<void> ctx;
   Function<bool,Pointer<const struct wclap_output_events> list,
                            Pointer<const wclap_event_header_t>       event> try_push;
};
struct wclap_audio_buffer {
   Pointer<Pointer<float>>  data32;
   Pointer<Pointer<double>> data64;
   uint32_t channel_count;
   uint32_t latency;
   uint64_t constant_mask;
};
typedef int32_t wclap_process_status;
struct wclap_process {
   int64_t steady_time;
   uint32_t frames_count;
   Pointer<const wclap_event_transport_t> transport;
   Pointer<const wclap_audio_buffer_t> audio_inputs;
   Pointer<wclap_audio_buffer_t>       audio_outputs;
   uint32_t                   audio_inputs_count;
   uint32_t                   audio_outputs_count;
   Pointer<const wclap_input_events_t>  in_events;
   Pointer<const wclap_output_events_t> out_events;
};
struct wclap_plugin_descriptor {
   wclap_version_t wclap_version;
   Pointer<const char> id;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> manual_url;
   Pointer<const char> support_url;
   Pointer<const char> version;
   Pointer<const char> description;
   Pointer<const char> Pointer<const> features;
};
struct wclap_plugin {
   Pointer<const wclap_plugin_descriptor_t> desc;

   Pointer<void> plugin_data;
   Function<bool,Pointer<const struct wclap_plugin> plugin> init;
   Function<void,Pointer<const struct wclap_plugin> plugin> destroy;
   Function<bool,Pointer<const struct wclap_plugin> plugin,
                            double                    sample_rate,
                            uint32_t                  min_frames_count,
                            uint32_t                  max_frames_count> activate;
   Function<void,Pointer<const struct wclap_plugin> plugin> deactivate;
   Function<bool,Pointer<const struct wclap_plugin> plugin> start_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> stop_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> reset;
   Function<wclap_process_status,Pointer<const struct wclap_plugin> plugin,
                                          Pointer<const wclap_process_t>     process> process;
   Function<Pointer<const void> ,Pointer<const struct wclap_plugin> plugin, Pointer<const char> id> get_extension;
   Function<void,Pointer<const struct wclap_plugin> plugin> on_main_thread;
};
struct wclap_audio_port_info {
   wclap_id id;
   char    name[CLAP_NAME_SIZE];

   uint32_t flags;
   uint32_t channel_count;
   Pointer<const char> port_type;
   wclap_id in_place_pair;
};
struct wclap_plugin_audio_ports {
   Function<uint32_t,Pointer<const wclap_plugin_t> plugin, bool is_input> count;
   Function<bool,Pointer<const wclap_plugin_t>    plugin,
                       uint32_t                index,
                       bool                    is_input,
                       Pointer<wclap_audio_port_info_t> info> get;
};
struct wclap_host_audio_ports {
   Function<bool,Pointer<const wclap_host_t> host, uint32_t flag> is_rescan_flag_supported;
   Function<void,Pointer<const wclap_host_t> host, uint32_t flags> rescan;
};
struct wclap_plugin_extensible_audio_ports {
   Function<bool,Pointer<const wclap_plugin_t> plugin,
                            bool                 is_input,
                            uint32_t             channel_count,
                            Pointer<const char>          port_type,
                            Pointer<const void>          port_details> add_port;
   Function<bool,Pointer<const wclap_plugin_t> plugin, bool is_input, uint32_t index> remove_port;
};
struct wclap_version {
   uint32_t major;
   uint32_t minor;
   uint32_t revision;
};
struct wclap_host {
   wclap_version_t wclap_version;

   Pointer<void> host_data;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> version;
   Function<Pointer<const void> ,Pointer<const struct wclap_host> host, Pointer<const char> extension_id> get_extension;
   Function<void,Pointer<const struct wclap_host> host> request_restart;
   Function<void,Pointer<const struct wclap_host> host> request_process;
   Function<void,Pointer<const struct wclap_host> host> request_callback;
};
typedef int64_t wclap_beattime;
typedef int64_t wclap_sectime;
typedef uint32_t wclap_id;
typedef int32_t wclap_note_expression;
struct wclap_event_header {
   uint32_t size;
   uint32_t time;
   uint16_t space_id;
   uint16_t type;
   uint32_t flags;
};
struct wclap_event_note {
   wclap_event_header_t header;

   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;
   double  velocity;
};
struct wclap_event_note_expression {
   wclap_event_header_t header;

   wclap_note_expression expression_id;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_value {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_mod {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double amount;
};
struct wclap_event_param_gesture {
   wclap_event_header_t header;
   wclap_id param_id;
};
struct wclap_event_transport {
   wclap_event_header_t header;

   uint32_t flags;

   wclap_beattime song_pos_beats;
   wclap_sectime  song_pos_seconds;

   double tempo;
   double tempo_inc;

   wclap_beattime loop_start_beats;
   wclap_beattime loop_end_beats;
   wclap_sectime  loop_start_seconds;
   wclap_sectime  loop_end_seconds;

   wclap_beattime bar_start;
   int32_t       bar_number;

   uint16_t tsig_num;
   uint16_t tsig_denom;
};
struct wclap_event_midi {
   wclap_event_header_t header;

   uint16_t port_index;
   uint8_t  data[3];
};
struct wclap_event_midi_sysex {
   wclap_event_header_t header;

   uint16_t       port_index;
   Pointer<const uint8_t> buffer;
   uint32_t       size;
};
struct wclap_event_midi2 {
   wclap_event_header_t header;

   uint16_t port_index;
   uint32_t data[4];
};
struct wclap_input_events {
   Pointer<void> ctx;
   Function<uint32_t,Pointer<const struct wclap_input_events> list> size;
   Function<Pointer<const wclap_event_header_t> ,Pointer<const struct wclap_input_events> list, uint32_t index> get;
};
struct wclap_output_events {
   Pointer<void> ctx;
   Function<bool,Pointer<const struct wclap_output_events> list,
                            Pointer<const wclap_event_header_t>       event> try_push;
};
struct wclap_audio_buffer {
   Pointer<Pointer<float>>  data32;
   Pointer<Pointer<double>> data64;
   uint32_t channel_count;
   uint32_t latency;
   uint64_t constant_mask;
};
typedef int32_t wclap_process_status;
struct wclap_process {
   int64_t steady_time;
   uint32_t frames_count;
   Pointer<const wclap_event_transport_t> transport;
   Pointer<const wclap_audio_buffer_t> audio_inputs;
   Pointer<wclap_audio_buffer_t>       audio_outputs;
   uint32_t                   audio_inputs_count;
   uint32_t                   audio_outputs_count;
   Pointer<const wclap_input_events_t>  in_events;
   Pointer<const wclap_output_events_t> out_events;
};
struct wclap_plugin_descriptor {
   wclap_version_t wclap_version;
   Pointer<const char> id;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> manual_url;
   Pointer<const char> support_url;
   Pointer<const char> version;
   Pointer<const char> description;
   Pointer<const char> Pointer<const> features;
};
struct wclap_plugin {
   Pointer<const wclap_plugin_descriptor_t> desc;

   Pointer<void> plugin_data;
   Function<bool,Pointer<const struct wclap_plugin> plugin> init;
   Function<void,Pointer<const struct wclap_plugin> plugin> destroy;
   Function<bool,Pointer<const struct wclap_plugin> plugin,
                            double                    sample_rate,
                            uint32_t                  min_frames_count,
                            uint32_t                  max_frames_count> activate;
   Function<void,Pointer<const struct wclap_plugin> plugin> deactivate;
   Function<bool,Pointer<const struct wclap_plugin> plugin> start_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> stop_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> reset;
   Function<wclap_process_status,Pointer<const struct wclap_plugin> plugin,
                                          Pointer<const wclap_process_t>     process> process;
   Function<Pointer<const void> ,Pointer<const struct wclap_plugin> plugin, Pointer<const char> id> get_extension;
   Function<void,Pointer<const struct wclap_plugin> plugin> on_main_thread;
};
struct wclap_plugin_gain_adjustment_metering {
  Function<double,Pointer<const wclap_plugin_t> plugin> get;
};
struct wclap_version {
   uint32_t major;
   uint32_t minor;
   uint32_t revision;
};
struct wclap_host {
   wclap_version_t wclap_version;

   Pointer<void> host_data;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> version;
   Function<Pointer<const void> ,Pointer<const struct wclap_host> host, Pointer<const char> extension_id> get_extension;
   Function<void,Pointer<const struct wclap_host> host> request_restart;
   Function<void,Pointer<const struct wclap_host> host> request_process;
   Function<void,Pointer<const struct wclap_host> host> request_callback;
};
typedef int64_t wclap_beattime;
typedef int64_t wclap_sectime;
typedef uint32_t wclap_id;
typedef int32_t wclap_note_expression;
struct wclap_event_header {
   uint32_t size;
   uint32_t time;
   uint16_t space_id;
   uint16_t type;
   uint32_t flags;
};
struct wclap_event_note {
   wclap_event_header_t header;

   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;
   double  velocity;
};
struct wclap_event_note_expression {
   wclap_event_header_t header;

   wclap_note_expression expression_id;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_value {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_mod {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double amount;
};
struct wclap_event_param_gesture {
   wclap_event_header_t header;
   wclap_id param_id;
};
struct wclap_event_transport {
   wclap_event_header_t header;

   uint32_t flags;

   wclap_beattime song_pos_beats;
   wclap_sectime  song_pos_seconds;

   double tempo;
   double tempo_inc;

   wclap_beattime loop_start_beats;
   wclap_beattime loop_end_beats;
   wclap_sectime  loop_start_seconds;
   wclap_sectime  loop_end_seconds;

   wclap_beattime bar_start;
   int32_t       bar_number;

   uint16_t tsig_num;
   uint16_t tsig_denom;
};
struct wclap_event_midi {
   wclap_event_header_t header;

   uint16_t port_index;
   uint8_t  data[3];
};
struct wclap_event_midi_sysex {
   wclap_event_header_t header;

   uint16_t       port_index;
   Pointer<const uint8_t> buffer;
   uint32_t       size;
};
struct wclap_event_midi2 {
   wclap_event_header_t header;

   uint16_t port_index;
   uint32_t data[4];
};
struct wclap_input_events {
   Pointer<void> ctx;
   Function<uint32_t,Pointer<const struct wclap_input_events> list> size;
   Function<Pointer<const wclap_event_header_t> ,Pointer<const struct wclap_input_events> list, uint32_t index> get;
};
struct wclap_output_events {
   Pointer<void> ctx;
   Function<bool,Pointer<const struct wclap_output_events> list,
                            Pointer<const wclap_event_header_t>       event> try_push;
};
struct wclap_audio_buffer {
   Pointer<Pointer<float>>  data32;
   Pointer<Pointer<double>> data64;
   uint32_t channel_count;
   uint32_t latency;
   uint64_t constant_mask;
};
typedef int32_t wclap_process_status;
struct wclap_process {
   int64_t steady_time;
   uint32_t frames_count;
   Pointer<const wclap_event_transport_t> transport;
   Pointer<const wclap_audio_buffer_t> audio_inputs;
   Pointer<wclap_audio_buffer_t>       audio_outputs;
   uint32_t                   audio_inputs_count;
   uint32_t                   audio_outputs_count;
   Pointer<const wclap_input_events_t>  in_events;
   Pointer<const wclap_output_events_t> out_events;
};
struct wclap_plugin_descriptor {
   wclap_version_t wclap_version;
   Pointer<const char> id;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> manual_url;
   Pointer<const char> support_url;
   Pointer<const char> version;
   Pointer<const char> description;
   Pointer<const char> Pointer<const> features;
};
struct wclap_plugin {
   Pointer<const wclap_plugin_descriptor_t> desc;

   Pointer<void> plugin_data;
   Function<bool,Pointer<const struct wclap_plugin> plugin> init;
   Function<void,Pointer<const struct wclap_plugin> plugin> destroy;
   Function<bool,Pointer<const struct wclap_plugin> plugin,
                            double                    sample_rate,
                            uint32_t                  min_frames_count,
                            uint32_t                  max_frames_count> activate;
   Function<void,Pointer<const struct wclap_plugin> plugin> deactivate;
   Function<bool,Pointer<const struct wclap_plugin> plugin> start_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> stop_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> reset;
   Function<wclap_process_status,Pointer<const struct wclap_plugin> plugin,
                                          Pointer<const wclap_process_t>     process> process;
   Function<Pointer<const void> ,Pointer<const struct wclap_plugin> plugin, Pointer<const char> id> get_extension;
   Function<void,Pointer<const struct wclap_plugin> plugin> on_main_thread;
};
struct wclap_mini_curve_display_curve_hints {
   double x_min;
   double x_max;
   double y_min;
   double y_max;

};
struct wclap_mini_curve_display_curve_data {
   int32_t curve_kind;
   Pointer<uint16_t> values;
   uint32_t  values_count;
};
struct wclap_plugin_mini_curve_display {
   Function<uint32_t,Pointer<const wclap_plugin_t> plugin> get_curve_count;
   Function<uint32_t,Pointer<const wclap_plugin_t>                  plugin,
                              Pointer<wclap_mini_curve_display_curve_data_t> curves,
                              uint32_t                              curves_size> render;
   Function<void,Pointer<const wclap_plugin_t> plugin, bool is_observed> set_observed;
   Function<bool,Pointer<const wclap_plugin_t> plugin,
                                 uint32_t             curve_index,
                                 Pointer<char>                x_name,
                                 Pointer<char>                y_name,
                                 uint32_t             name_capacity> get_axis_name;
};
struct wclap_host_mini_curve_display {
   Function<bool,Pointer<const wclap_host_t>                     host,
                             uint32_t                               kind,
                             Pointer<wclap_mini_curve_display_curve_hints_t> hints> get_hints;
   Function<void,Pointer<const wclap_host_t> host, bool is_dynamic> set_dynamic;
   Function<void,Pointer<const wclap_host_t> host, uint32_t flags> changed;
};
struct wclap_color {
   uint8_t alpha;
   uint8_t red;
   uint8_t green;
   uint8_t blue;
};
struct wclap_version {
   uint32_t major;
   uint32_t minor;
   uint32_t revision;
};
struct wclap_host {
   wclap_version_t wclap_version;

   Pointer<void> host_data;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> version;
   Function<Pointer<const void> ,Pointer<const struct wclap_host> host, Pointer<const char> extension_id> get_extension;
   Function<void,Pointer<const struct wclap_host> host> request_restart;
   Function<void,Pointer<const struct wclap_host> host> request_process;
   Function<void,Pointer<const struct wclap_host> host> request_callback;
};
typedef int64_t wclap_beattime;
typedef int64_t wclap_sectime;
typedef uint32_t wclap_id;
typedef int32_t wclap_note_expression;
struct wclap_event_header {
   uint32_t size;
   uint32_t time;
   uint16_t space_id;
   uint16_t type;
   uint32_t flags;
};
struct wclap_event_note {
   wclap_event_header_t header;

   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;
   double  velocity;
};
struct wclap_event_note_expression {
   wclap_event_header_t header;

   wclap_note_expression expression_id;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_value {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_mod {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double amount;
};
struct wclap_event_param_gesture {
   wclap_event_header_t header;
   wclap_id param_id;
};
struct wclap_event_transport {
   wclap_event_header_t header;

   uint32_t flags;

   wclap_beattime song_pos_beats;
   wclap_sectime  song_pos_seconds;

   double tempo;
   double tempo_inc;

   wclap_beattime loop_start_beats;
   wclap_beattime loop_end_beats;
   wclap_sectime  loop_start_seconds;
   wclap_sectime  loop_end_seconds;

   wclap_beattime bar_start;
   int32_t       bar_number;

   uint16_t tsig_num;
   uint16_t tsig_denom;
};
struct wclap_event_midi {
   wclap_event_header_t header;

   uint16_t port_index;
   uint8_t  data[3];
};
struct wclap_event_midi_sysex {
   wclap_event_header_t header;

   uint16_t       port_index;
   Pointer<const uint8_t> buffer;
   uint32_t       size;
};
struct wclap_event_midi2 {
   wclap_event_header_t header;

   uint16_t port_index;
   uint32_t data[4];
};
struct wclap_input_events {
   Pointer<void> ctx;
   Function<uint32_t,Pointer<const struct wclap_input_events> list> size;
   Function<Pointer<const wclap_event_header_t> ,Pointer<const struct wclap_input_events> list, uint32_t index> get;
};
struct wclap_output_events {
   Pointer<void> ctx;
   Function<bool,Pointer<const struct wclap_output_events> list,
                            Pointer<const wclap_event_header_t>       event> try_push;
};
struct wclap_audio_buffer {
   Pointer<Pointer<float>>  data32;
   Pointer<Pointer<double>> data64;
   uint32_t channel_count;
   uint32_t latency;
   uint64_t constant_mask;
};
typedef int32_t wclap_process_status;
struct wclap_process {
   int64_t steady_time;
   uint32_t frames_count;
   Pointer<const wclap_event_transport_t> transport;
   Pointer<const wclap_audio_buffer_t> audio_inputs;
   Pointer<wclap_audio_buffer_t>       audio_outputs;
   uint32_t                   audio_inputs_count;
   uint32_t                   audio_outputs_count;
   Pointer<const wclap_input_events_t>  in_events;
   Pointer<const wclap_output_events_t> out_events;
};
struct wclap_plugin_descriptor {
   wclap_version_t wclap_version;
   Pointer<const char> id;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> manual_url;
   Pointer<const char> support_url;
   Pointer<const char> version;
   Pointer<const char> description;
   Pointer<const char> Pointer<const> features;
};
struct wclap_plugin {
   Pointer<const wclap_plugin_descriptor_t> desc;

   Pointer<void> plugin_data;
   Function<bool,Pointer<const struct wclap_plugin> plugin> init;
   Function<void,Pointer<const struct wclap_plugin> plugin> destroy;
   Function<bool,Pointer<const struct wclap_plugin> plugin,
                            double                    sample_rate,
                            uint32_t                  min_frames_count,
                            uint32_t                  max_frames_count> activate;
   Function<void,Pointer<const struct wclap_plugin> plugin> deactivate;
   Function<bool,Pointer<const struct wclap_plugin> plugin> start_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> stop_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> reset;
   Function<wclap_process_status,Pointer<const struct wclap_plugin> plugin,
                                          Pointer<const wclap_process_t>     process> process;
   Function<Pointer<const void> ,Pointer<const struct wclap_plugin> plugin, Pointer<const char> id> get_extension;
   Function<void,Pointer<const struct wclap_plugin> plugin> on_main_thread;
};
struct wclap_project_location_element {
   uint64_t flags;
   uint32_t kind;
   uint32_t track_kind;
   uint32_t index;
   char id[CLAP_PATH_SIZE];
   char name[CLAP_NAME_SIZE];
   wclap_color_t color;
};
struct wclap_plugin_project_location {
   Function<void,Pointer<const wclap_plugin_t>                  plugin,
                       Pointer<const wclap_project_location_element_t> path,
                       uint32_t                              num_elements> set;
};
struct wclap_version {
   uint32_t major;
   uint32_t minor;
   uint32_t revision;
};
struct wclap_host {
   wclap_version_t wclap_version;

   Pointer<void> host_data;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> version;
   Function<Pointer<const void> ,Pointer<const struct wclap_host> host, Pointer<const char> extension_id> get_extension;
   Function<void,Pointer<const struct wclap_host> host> request_restart;
   Function<void,Pointer<const struct wclap_host> host> request_process;
   Function<void,Pointer<const struct wclap_host> host> request_callback;
};
typedef int64_t wclap_beattime;
typedef int64_t wclap_sectime;
typedef uint32_t wclap_id;
typedef int32_t wclap_note_expression;
struct wclap_event_header {
   uint32_t size;
   uint32_t time;
   uint16_t space_id;
   uint16_t type;
   uint32_t flags;
};
struct wclap_event_note {
   wclap_event_header_t header;

   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;
   double  velocity;
};
struct wclap_event_note_expression {
   wclap_event_header_t header;

   wclap_note_expression expression_id;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_value {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_mod {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double amount;
};
struct wclap_event_param_gesture {
   wclap_event_header_t header;
   wclap_id param_id;
};
struct wclap_event_transport {
   wclap_event_header_t header;

   uint32_t flags;

   wclap_beattime song_pos_beats;
   wclap_sectime  song_pos_seconds;

   double tempo;
   double tempo_inc;

   wclap_beattime loop_start_beats;
   wclap_beattime loop_end_beats;
   wclap_sectime  loop_start_seconds;
   wclap_sectime  loop_end_seconds;

   wclap_beattime bar_start;
   int32_t       bar_number;

   uint16_t tsig_num;
   uint16_t tsig_denom;
};
struct wclap_event_midi {
   wclap_event_header_t header;

   uint16_t port_index;
   uint8_t  data[3];
};
struct wclap_event_midi_sysex {
   wclap_event_header_t header;

   uint16_t       port_index;
   Pointer<const uint8_t> buffer;
   uint32_t       size;
};
struct wclap_event_midi2 {
   wclap_event_header_t header;

   uint16_t port_index;
   uint32_t data[4];
};
struct wclap_input_events {
   Pointer<void> ctx;
   Function<uint32_t,Pointer<const struct wclap_input_events> list> size;
   Function<Pointer<const wclap_event_header_t> ,Pointer<const struct wclap_input_events> list, uint32_t index> get;
};
struct wclap_output_events {
   Pointer<void> ctx;
   Function<bool,Pointer<const struct wclap_output_events> list,
                            Pointer<const wclap_event_header_t>       event> try_push;
};
struct wclap_audio_buffer {
   Pointer<Pointer<float>>  data32;
   Pointer<Pointer<double>> data64;
   uint32_t channel_count;
   uint32_t latency;
   uint64_t constant_mask;
};
typedef int32_t wclap_process_status;
struct wclap_process {
   int64_t steady_time;
   uint32_t frames_count;
   Pointer<const wclap_event_transport_t> transport;
   Pointer<const wclap_audio_buffer_t> audio_inputs;
   Pointer<wclap_audio_buffer_t>       audio_outputs;
   uint32_t                   audio_inputs_count;
   uint32_t                   audio_outputs_count;
   Pointer<const wclap_input_events_t>  in_events;
   Pointer<const wclap_output_events_t> out_events;
};
struct wclap_plugin_descriptor {
   wclap_version_t wclap_version;
   Pointer<const char> id;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> manual_url;
   Pointer<const char> support_url;
   Pointer<const char> version;
   Pointer<const char> description;
   Pointer<const char> Pointer<const> features;
};
struct wclap_plugin {
   Pointer<const wclap_plugin_descriptor_t> desc;

   Pointer<void> plugin_data;
   Function<bool,Pointer<const struct wclap_plugin> plugin> init;
   Function<void,Pointer<const struct wclap_plugin> plugin> destroy;
   Function<bool,Pointer<const struct wclap_plugin> plugin,
                            double                    sample_rate,
                            uint32_t                  min_frames_count,
                            uint32_t                  max_frames_count> activate;
   Function<void,Pointer<const struct wclap_plugin> plugin> deactivate;
   Function<bool,Pointer<const struct wclap_plugin> plugin> start_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> stop_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> reset;
   Function<wclap_process_status,Pointer<const struct wclap_plugin> plugin,
                                          Pointer<const wclap_process_t>     process> process;
   Function<Pointer<const void> ,Pointer<const struct wclap_plugin> plugin, Pointer<const char> id> get_extension;
   Function<void,Pointer<const struct wclap_plugin> plugin> on_main_thread;
};
struct wclap_plugin_resource_directory {
   Function<void,Pointer<const wclap_plugin_t> plugin, Pointer<const char> path, bool is_shared> set_directory;
   Function<void,Pointer<const wclap_plugin_t> plugin, bool all> collect;
   Function<uint32_t,Pointer<const wclap_plugin_t> plugin> get_files_count;
   Function<int32_t,Pointer<const wclap_plugin_t> plugin,
                                    uint32_t             index,
                                    Pointer<char>                path,
                                    uint32_t             path_size> get_file_path;
};
struct wclap_host_resource_directory {
   Function<bool,Pointer<const wclap_host_t> host, bool is_shared> request_directory;
   Function<void,Pointer<const wclap_host_t> host, bool is_shared> release_directory;
};
struct wclap_version {
   uint32_t major;
   uint32_t minor;
   uint32_t revision;
};
struct wclap_host {
   wclap_version_t wclap_version;

   Pointer<void> host_data;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> version;
   Function<Pointer<const void> ,Pointer<const struct wclap_host> host, Pointer<const char> extension_id> get_extension;
   Function<void,Pointer<const struct wclap_host> host> request_restart;
   Function<void,Pointer<const struct wclap_host> host> request_process;
   Function<void,Pointer<const struct wclap_host> host> request_callback;
};
typedef int64_t wclap_beattime;
typedef int64_t wclap_sectime;
typedef uint32_t wclap_id;
typedef int32_t wclap_note_expression;
struct wclap_event_header {
   uint32_t size;
   uint32_t time;
   uint16_t space_id;
   uint16_t type;
   uint32_t flags;
};
struct wclap_event_note {
   wclap_event_header_t header;

   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;
   double  velocity;
};
struct wclap_event_note_expression {
   wclap_event_header_t header;

   wclap_note_expression expression_id;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_value {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_mod {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double amount;
};
struct wclap_event_param_gesture {
   wclap_event_header_t header;
   wclap_id param_id;
};
struct wclap_event_transport {
   wclap_event_header_t header;

   uint32_t flags;

   wclap_beattime song_pos_beats;
   wclap_sectime  song_pos_seconds;

   double tempo;
   double tempo_inc;

   wclap_beattime loop_start_beats;
   wclap_beattime loop_end_beats;
   wclap_sectime  loop_start_seconds;
   wclap_sectime  loop_end_seconds;

   wclap_beattime bar_start;
   int32_t       bar_number;

   uint16_t tsig_num;
   uint16_t tsig_denom;
};
struct wclap_event_midi {
   wclap_event_header_t header;

   uint16_t port_index;
   uint8_t  data[3];
};
struct wclap_event_midi_sysex {
   wclap_event_header_t header;

   uint16_t       port_index;
   Pointer<const uint8_t> buffer;
   uint32_t       size;
};
struct wclap_event_midi2 {
   wclap_event_header_t header;

   uint16_t port_index;
   uint32_t data[4];
};
struct wclap_input_events {
   Pointer<void> ctx;
   Function<uint32_t,Pointer<const struct wclap_input_events> list> size;
   Function<Pointer<const wclap_event_header_t> ,Pointer<const struct wclap_input_events> list, uint32_t index> get;
};
struct wclap_output_events {
   Pointer<void> ctx;
   Function<bool,Pointer<const struct wclap_output_events> list,
                            Pointer<const wclap_event_header_t>       event> try_push;
};
struct wclap_audio_buffer {
   Pointer<Pointer<float>>  data32;
   Pointer<Pointer<double>> data64;
   uint32_t channel_count;
   uint32_t latency;
   uint64_t constant_mask;
};
typedef int32_t wclap_process_status;
struct wclap_process {
   int64_t steady_time;
   uint32_t frames_count;
   Pointer<const wclap_event_transport_t> transport;
   Pointer<const wclap_audio_buffer_t> audio_inputs;
   Pointer<wclap_audio_buffer_t>       audio_outputs;
   uint32_t                   audio_inputs_count;
   uint32_t                   audio_outputs_count;
   Pointer<const wclap_input_events_t>  in_events;
   Pointer<const wclap_output_events_t> out_events;
};
struct wclap_plugin_descriptor {
   wclap_version_t wclap_version;
   Pointer<const char> id;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> manual_url;
   Pointer<const char> support_url;
   Pointer<const char> version;
   Pointer<const char> description;
   Pointer<const char> Pointer<const> features;
};
struct wclap_plugin {
   Pointer<const wclap_plugin_descriptor_t> desc;

   Pointer<void> plugin_data;
   Function<bool,Pointer<const struct wclap_plugin> plugin> init;
   Function<void,Pointer<const struct wclap_plugin> plugin> destroy;
   Function<bool,Pointer<const struct wclap_plugin> plugin,
                            double                    sample_rate,
                            uint32_t                  min_frames_count,
                            uint32_t                  max_frames_count> activate;
   Function<void,Pointer<const struct wclap_plugin> plugin> deactivate;
   Function<bool,Pointer<const struct wclap_plugin> plugin> start_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> stop_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> reset;
   Function<wclap_process_status,Pointer<const struct wclap_plugin> plugin,
                                          Pointer<const wclap_process_t>     process> process;
   Function<Pointer<const void> ,Pointer<const struct wclap_plugin> plugin, Pointer<const char> id> get_extension;
   Function<void,Pointer<const struct wclap_plugin> plugin> on_main_thread;
};
struct wclap_host_scratch_memory {
   Function<bool,Pointer<const wclap_host_t> host,
                           uint32_t           scratch_size_bytes,
                           uint32_t           max_concurrency_hint> reserve;
   Function<Pointer<void> ,Pointer<const wclap_host_t> host> access;
};
struct wclap_version {
   uint32_t major;
   uint32_t minor;
   uint32_t revision;
};
struct wclap_host {
   wclap_version_t wclap_version;

   Pointer<void> host_data;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> version;
   Function<Pointer<const void> ,Pointer<const struct wclap_host> host, Pointer<const char> extension_id> get_extension;
   Function<void,Pointer<const struct wclap_host> host> request_restart;
   Function<void,Pointer<const struct wclap_host> host> request_process;
   Function<void,Pointer<const struct wclap_host> host> request_callback;
};
typedef int64_t wclap_beattime;
typedef int64_t wclap_sectime;
typedef uint32_t wclap_id;
typedef int32_t wclap_note_expression;
struct wclap_event_header {
   uint32_t size;
   uint32_t time;
   uint16_t space_id;
   uint16_t type;
   uint32_t flags;
};
struct wclap_event_note {
   wclap_event_header_t header;

   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;
   double  velocity;
};
struct wclap_event_note_expression {
   wclap_event_header_t header;

   wclap_note_expression expression_id;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_value {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_mod {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double amount;
};
struct wclap_event_param_gesture {
   wclap_event_header_t header;
   wclap_id param_id;
};
struct wclap_event_transport {
   wclap_event_header_t header;

   uint32_t flags;

   wclap_beattime song_pos_beats;
   wclap_sectime  song_pos_seconds;

   double tempo;
   double tempo_inc;

   wclap_beattime loop_start_beats;
   wclap_beattime loop_end_beats;
   wclap_sectime  loop_start_seconds;
   wclap_sectime  loop_end_seconds;

   wclap_beattime bar_start;
   int32_t       bar_number;

   uint16_t tsig_num;
   uint16_t tsig_denom;
};
struct wclap_event_midi {
   wclap_event_header_t header;

   uint16_t port_index;
   uint8_t  data[3];
};
struct wclap_event_midi_sysex {
   wclap_event_header_t header;

   uint16_t       port_index;
   Pointer<const uint8_t> buffer;
   uint32_t       size;
};
struct wclap_event_midi2 {
   wclap_event_header_t header;

   uint16_t port_index;
   uint32_t data[4];
};
struct wclap_input_events {
   Pointer<void> ctx;
   Function<uint32_t,Pointer<const struct wclap_input_events> list> size;
   Function<Pointer<const wclap_event_header_t> ,Pointer<const struct wclap_input_events> list, uint32_t index> get;
};
struct wclap_output_events {
   Pointer<void> ctx;
   Function<bool,Pointer<const struct wclap_output_events> list,
                            Pointer<const wclap_event_header_t>       event> try_push;
};
struct wclap_audio_buffer {
   Pointer<Pointer<float>>  data32;
   Pointer<Pointer<double>> data64;
   uint32_t channel_count;
   uint32_t latency;
   uint64_t constant_mask;
};
typedef int32_t wclap_process_status;
struct wclap_process {
   int64_t steady_time;
   uint32_t frames_count;
   Pointer<const wclap_event_transport_t> transport;
   Pointer<const wclap_audio_buffer_t> audio_inputs;
   Pointer<wclap_audio_buffer_t>       audio_outputs;
   uint32_t                   audio_inputs_count;
   uint32_t                   audio_outputs_count;
   Pointer<const wclap_input_events_t>  in_events;
   Pointer<const wclap_output_events_t> out_events;
};
struct wclap_plugin_descriptor {
   wclap_version_t wclap_version;
   Pointer<const char> id;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> manual_url;
   Pointer<const char> support_url;
   Pointer<const char> version;
   Pointer<const char> description;
   Pointer<const char> Pointer<const> features;
};
struct wclap_plugin {
   Pointer<const wclap_plugin_descriptor_t> desc;

   Pointer<void> plugin_data;
   Function<bool,Pointer<const struct wclap_plugin> plugin> init;
   Function<void,Pointer<const struct wclap_plugin> plugin> destroy;
   Function<bool,Pointer<const struct wclap_plugin> plugin,
                            double                    sample_rate,
                            uint32_t                  min_frames_count,
                            uint32_t                  max_frames_count> activate;
   Function<void,Pointer<const struct wclap_plugin> plugin> deactivate;
   Function<bool,Pointer<const struct wclap_plugin> plugin> start_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> stop_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> reset;
   Function<wclap_process_status,Pointer<const struct wclap_plugin> plugin,
                                          Pointer<const wclap_process_t>     process> process;
   Function<Pointer<const void> ,Pointer<const struct wclap_plugin> plugin, Pointer<const char> id> get_extension;
   Function<void,Pointer<const struct wclap_plugin> plugin> on_main_thread;
};
struct wclap_host_transport_control {
   Function<void,Pointer<const wclap_host_t> host> request_start;
   Function<void,Pointer<const wclap_host_t> host> request_stop;
   Function<void,Pointer<const wclap_host_t> host> request_continue;
   Function<void,Pointer<const wclap_host_t> host> request_pause;
   Function<void,Pointer<const wclap_host_t> host> request_toggle_play;
   Function<void,Pointer<const wclap_host_t> host, wclap_beattime position> request_jump;
   Function<void,Pointer<const wclap_host_t> host,
                                       wclap_beattime      start,
                                       wclap_beattime      duration> request_loop_region;
   Function<void,Pointer<const wclap_host_t> host> request_toggle_loop;
   Function<void,Pointer<const wclap_host_t> host, bool is_enabled> request_enable_loop;
   Function<void,Pointer<const wclap_host_t> host, bool is_recording> request_record;
   Function<void,Pointer<const wclap_host_t> host> request_toggle_record;
};
struct wclap_version {
   uint32_t major;
   uint32_t minor;
   uint32_t revision;
};
struct wclap_host {
   wclap_version_t wclap_version;

   Pointer<void> host_data;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> version;
   Function<Pointer<const void> ,Pointer<const struct wclap_host> host, Pointer<const char> extension_id> get_extension;
   Function<void,Pointer<const struct wclap_host> host> request_restart;
   Function<void,Pointer<const struct wclap_host> host> request_process;
   Function<void,Pointer<const struct wclap_host> host> request_callback;
};
typedef int64_t wclap_beattime;
typedef int64_t wclap_sectime;
typedef uint32_t wclap_id;
typedef int32_t wclap_note_expression;
struct wclap_event_header {
   uint32_t size;
   uint32_t time;
   uint16_t space_id;
   uint16_t type;
   uint32_t flags;
};
struct wclap_event_note {
   wclap_event_header_t header;

   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;
   double  velocity;
};
struct wclap_event_note_expression {
   wclap_event_header_t header;

   wclap_note_expression expression_id;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_value {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_mod {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double amount;
};
struct wclap_event_param_gesture {
   wclap_event_header_t header;
   wclap_id param_id;
};
struct wclap_event_transport {
   wclap_event_header_t header;

   uint32_t flags;

   wclap_beattime song_pos_beats;
   wclap_sectime  song_pos_seconds;

   double tempo;
   double tempo_inc;

   wclap_beattime loop_start_beats;
   wclap_beattime loop_end_beats;
   wclap_sectime  loop_start_seconds;
   wclap_sectime  loop_end_seconds;

   wclap_beattime bar_start;
   int32_t       bar_number;

   uint16_t tsig_num;
   uint16_t tsig_denom;
};
struct wclap_event_midi {
   wclap_event_header_t header;

   uint16_t port_index;
   uint8_t  data[3];
};
struct wclap_event_midi_sysex {
   wclap_event_header_t header;

   uint16_t       port_index;
   Pointer<const uint8_t> buffer;
   uint32_t       size;
};
struct wclap_event_midi2 {
   wclap_event_header_t header;

   uint16_t port_index;
   uint32_t data[4];
};
struct wclap_input_events {
   Pointer<void> ctx;
   Function<uint32_t,Pointer<const struct wclap_input_events> list> size;
   Function<Pointer<const wclap_event_header_t> ,Pointer<const struct wclap_input_events> list, uint32_t index> get;
};
struct wclap_output_events {
   Pointer<void> ctx;
   Function<bool,Pointer<const struct wclap_output_events> list,
                            Pointer<const wclap_event_header_t>       event> try_push;
};
struct wclap_audio_buffer {
   Pointer<Pointer<float>>  data32;
   Pointer<Pointer<double>> data64;
   uint32_t channel_count;
   uint32_t latency;
   uint64_t constant_mask;
};
typedef int32_t wclap_process_status;
struct wclap_process {
   int64_t steady_time;
   uint32_t frames_count;
   Pointer<const wclap_event_transport_t> transport;
   Pointer<const wclap_audio_buffer_t> audio_inputs;
   Pointer<wclap_audio_buffer_t>       audio_outputs;
   uint32_t                   audio_inputs_count;
   uint32_t                   audio_outputs_count;
   Pointer<const wclap_input_events_t>  in_events;
   Pointer<const wclap_output_events_t> out_events;
};
struct wclap_plugin_descriptor {
   wclap_version_t wclap_version;
   Pointer<const char> id;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> manual_url;
   Pointer<const char> support_url;
   Pointer<const char> version;
   Pointer<const char> description;
   Pointer<const char> Pointer<const> features;
};
struct wclap_plugin {
   Pointer<const wclap_plugin_descriptor_t> desc;

   Pointer<void> plugin_data;
   Function<bool,Pointer<const struct wclap_plugin> plugin> init;
   Function<void,Pointer<const struct wclap_plugin> plugin> destroy;
   Function<bool,Pointer<const struct wclap_plugin> plugin,
                            double                    sample_rate,
                            uint32_t                  min_frames_count,
                            uint32_t                  max_frames_count> activate;
   Function<void,Pointer<const struct wclap_plugin> plugin> deactivate;
   Function<bool,Pointer<const struct wclap_plugin> plugin> start_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> stop_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> reset;
   Function<wclap_process_status,Pointer<const struct wclap_plugin> plugin,
                                          Pointer<const wclap_process_t>     process> process;
   Function<Pointer<const void> ,Pointer<const struct wclap_plugin> plugin, Pointer<const char> id> get_extension;
   Function<void,Pointer<const struct wclap_plugin> plugin> on_main_thread;
};
typedef int64_t wclap_beattime;
typedef int64_t wclap_sectime;
typedef uint32_t wclap_id;
typedef int32_t wclap_note_expression;
struct wclap_event_header {
   uint32_t size;
   uint32_t time;
   uint16_t space_id;
   uint16_t type;
   uint32_t flags;
};
struct wclap_event_note {
   wclap_event_header_t header;

   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;
   double  velocity;
};
struct wclap_event_note_expression {
   wclap_event_header_t header;

   wclap_note_expression expression_id;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_value {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_mod {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double amount;
};
struct wclap_event_param_gesture {
   wclap_event_header_t header;
   wclap_id param_id;
};
struct wclap_event_transport {
   wclap_event_header_t header;

   uint32_t flags;

   wclap_beattime song_pos_beats;
   wclap_sectime  song_pos_seconds;

   double tempo;
   double tempo_inc;

   wclap_beattime loop_start_beats;
   wclap_beattime loop_end_beats;
   wclap_sectime  loop_start_seconds;
   wclap_sectime  loop_end_seconds;

   wclap_beattime bar_start;
   int32_t       bar_number;

   uint16_t tsig_num;
   uint16_t tsig_denom;
};
struct wclap_event_midi {
   wclap_event_header_t header;

   uint16_t port_index;
   uint8_t  data[3];
};
struct wclap_event_midi_sysex {
   wclap_event_header_t header;

   uint16_t       port_index;
   Pointer<const uint8_t> buffer;
   uint32_t       size;
};
struct wclap_event_midi2 {
   wclap_event_header_t header;

   uint16_t port_index;
   uint32_t data[4];
};
struct wclap_input_events {
   Pointer<void> ctx;
   Function<uint32_t,Pointer<const struct wclap_input_events> list> size;
   Function<Pointer<const wclap_event_header_t> ,Pointer<const struct wclap_input_events> list, uint32_t index> get;
};
struct wclap_output_events {
   Pointer<void> ctx;
   Function<bool,Pointer<const struct wclap_output_events> list,
                            Pointer<const wclap_event_header_t>       event> try_push;
};
typedef uint32_t wclap_trigger_info_flags;
typedef uint32_t wclap_trigger_rescan_flags;
typedef uint32_t wclap_trigger_clear_flags;
struct wclap_event_trigger {
   wclap_event_header_t header;
   wclap_id trigger_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;
};
struct wclap_trigger_info {
   wclap_id id;

   wclap_trigger_info_flags flags;
   Pointer<void> cookie;
   char name[CLAP_NAME_SIZE];
   char module[CLAP_PATH_SIZE];
};
struct wclap_plugin_triggers {
   Function<uint32_t,Pointer<const wclap_plugin_t> plugin> count;
   Function<bool,Pointer<const wclap_plugin_t> plugin,
                            uint32_t             index,
                            Pointer<wclap_trigger_info_t> trigger_info> get_info;
};
struct wclap_host_triggers {
   Function<void,Pointer<const wclap_host_t> host, wclap_trigger_rescan_flags flags> rescan;
   Function<void,Pointer<const wclap_host_t>       host,
                         wclap_id                  trigger_id,
                         wclap_trigger_clear_flags flags> clear;
};
struct wclap_version {
   uint32_t major;
   uint32_t minor;
   uint32_t revision;
};
struct wclap_host {
   wclap_version_t wclap_version;

   Pointer<void> host_data;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> version;
   Function<Pointer<const void> ,Pointer<const struct wclap_host> host, Pointer<const char> extension_id> get_extension;
   Function<void,Pointer<const struct wclap_host> host> request_restart;
   Function<void,Pointer<const struct wclap_host> host> request_process;
   Function<void,Pointer<const struct wclap_host> host> request_callback;
};
typedef int64_t wclap_beattime;
typedef int64_t wclap_sectime;
typedef uint32_t wclap_id;
typedef int32_t wclap_note_expression;
struct wclap_event_header {
   uint32_t size;
   uint32_t time;
   uint16_t space_id;
   uint16_t type;
   uint32_t flags;
};
struct wclap_event_note {
   wclap_event_header_t header;

   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;
   double  velocity;
};
struct wclap_event_note_expression {
   wclap_event_header_t header;

   wclap_note_expression expression_id;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_value {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_mod {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double amount;
};
struct wclap_event_param_gesture {
   wclap_event_header_t header;
   wclap_id param_id;
};
struct wclap_event_transport {
   wclap_event_header_t header;

   uint32_t flags;

   wclap_beattime song_pos_beats;
   wclap_sectime  song_pos_seconds;

   double tempo;
   double tempo_inc;

   wclap_beattime loop_start_beats;
   wclap_beattime loop_end_beats;
   wclap_sectime  loop_start_seconds;
   wclap_sectime  loop_end_seconds;

   wclap_beattime bar_start;
   int32_t       bar_number;

   uint16_t tsig_num;
   uint16_t tsig_denom;
};
struct wclap_event_midi {
   wclap_event_header_t header;

   uint16_t port_index;
   uint8_t  data[3];
};
struct wclap_event_midi_sysex {
   wclap_event_header_t header;

   uint16_t       port_index;
   Pointer<const uint8_t> buffer;
   uint32_t       size;
};
struct wclap_event_midi2 {
   wclap_event_header_t header;

   uint16_t port_index;
   uint32_t data[4];
};
struct wclap_input_events {
   Pointer<void> ctx;
   Function<uint32_t,Pointer<const struct wclap_input_events> list> size;
   Function<Pointer<const wclap_event_header_t> ,Pointer<const struct wclap_input_events> list, uint32_t index> get;
};
struct wclap_output_events {
   Pointer<void> ctx;
   Function<bool,Pointer<const struct wclap_output_events> list,
                            Pointer<const wclap_event_header_t>       event> try_push;
};
struct wclap_audio_buffer {
   Pointer<Pointer<float>>  data32;
   Pointer<Pointer<double>> data64;
   uint32_t channel_count;
   uint32_t latency;
   uint64_t constant_mask;
};
typedef int32_t wclap_process_status;
struct wclap_process {
   int64_t steady_time;
   uint32_t frames_count;
   Pointer<const wclap_event_transport_t> transport;
   Pointer<const wclap_audio_buffer_t> audio_inputs;
   Pointer<wclap_audio_buffer_t>       audio_outputs;
   uint32_t                   audio_inputs_count;
   uint32_t                   audio_outputs_count;
   Pointer<const wclap_input_events_t>  in_events;
   Pointer<const wclap_output_events_t> out_events;
};
struct wclap_plugin_descriptor {
   wclap_version_t wclap_version;
   Pointer<const char> id;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> manual_url;
   Pointer<const char> support_url;
   Pointer<const char> version;
   Pointer<const char> description;
   Pointer<const char> Pointer<const> features;
};
struct wclap_plugin {
   Pointer<const wclap_plugin_descriptor_t> desc;

   Pointer<void> plugin_data;
   Function<bool,Pointer<const struct wclap_plugin> plugin> init;
   Function<void,Pointer<const struct wclap_plugin> plugin> destroy;
   Function<bool,Pointer<const struct wclap_plugin> plugin,
                            double                    sample_rate,
                            uint32_t                  min_frames_count,
                            uint32_t                  max_frames_count> activate;
   Function<void,Pointer<const struct wclap_plugin> plugin> deactivate;
   Function<bool,Pointer<const struct wclap_plugin> plugin> start_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> stop_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> reset;
   Function<wclap_process_status,Pointer<const struct wclap_plugin> plugin,
                                          Pointer<const wclap_process_t>     process> process;
   Function<Pointer<const void> ,Pointer<const struct wclap_plugin> plugin, Pointer<const char> id> get_extension;
   Function<void,Pointer<const struct wclap_plugin> plugin> on_main_thread;
};
typedef int64_t wclap_beattime;
typedef int64_t wclap_sectime;
typedef uint32_t wclap_id;
typedef int32_t wclap_note_expression;
struct wclap_event_header {
   uint32_t size;
   uint32_t time;
   uint16_t space_id;
   uint16_t type;
   uint32_t flags;
};
struct wclap_event_note {
   wclap_event_header_t header;

   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;
   double  velocity;
};
struct wclap_event_note_expression {
   wclap_event_header_t header;

   wclap_note_expression expression_id;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_value {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_mod {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double amount;
};
struct wclap_event_param_gesture {
   wclap_event_header_t header;
   wclap_id param_id;
};
struct wclap_event_transport {
   wclap_event_header_t header;

   uint32_t flags;

   wclap_beattime song_pos_beats;
   wclap_sectime  song_pos_seconds;

   double tempo;
   double tempo_inc;

   wclap_beattime loop_start_beats;
   wclap_beattime loop_end_beats;
   wclap_sectime  loop_start_seconds;
   wclap_sectime  loop_end_seconds;

   wclap_beattime bar_start;
   int32_t       bar_number;

   uint16_t tsig_num;
   uint16_t tsig_denom;
};
struct wclap_event_midi {
   wclap_event_header_t header;

   uint16_t port_index;
   uint8_t  data[3];
};
struct wclap_event_midi_sysex {
   wclap_event_header_t header;

   uint16_t       port_index;
   Pointer<const uint8_t> buffer;
   uint32_t       size;
};
struct wclap_event_midi2 {
   wclap_event_header_t header;

   uint16_t port_index;
   uint32_t data[4];
};
struct wclap_input_events {
   Pointer<void> ctx;
   Function<uint32_t,Pointer<const struct wclap_input_events> list> size;
   Function<Pointer<const wclap_event_header_t> ,Pointer<const struct wclap_input_events> list, uint32_t index> get;
};
struct wclap_output_events {
   Pointer<void> ctx;
   Function<bool,Pointer<const struct wclap_output_events> list,
                            Pointer<const wclap_event_header_t>       event> try_push;
};
struct wclap_event_tuning {
   wclap_event_header_t header;

   int16_t port_index;
   int16_t channel;
   wclap_id tunning_id;
};
struct wclap_tuning_info {
   wclap_id tuning_id;
   char    name[CLAP_NAME_SIZE];
   bool    is_dynamic;
};
struct wclap_plugin_tuning {
   Function<void,Pointer<const wclap_plugin_t> plugin> changed;
};
struct wclap_host_tuning {
   Function<double,Pointer<const wclap_host_t> host,
                                  wclap_id            tuning_id,
                                  int32_t            channel,
                                  int32_t            key,
                                  uint32_t           sample_offset> get_relative;
   Function<bool,Pointer<const wclap_host_t> host,
                               wclap_id            tuning_id,
                               int32_t            channel,
                               int32_t            key> should_play;
   Function<uint32_t,Pointer<const wclap_host_t> host> get_tuning_count;
   Function<bool,Pointer<const wclap_host_t>  host,
                            uint32_t            tuning_index,
                            Pointer<wclap_tuning_info_t> info> get_info;
};
struct wclap_version {
   uint32_t major;
   uint32_t minor;
   uint32_t revision;
};
struct wclap_host {
   wclap_version_t wclap_version;

   Pointer<void> host_data;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> version;
   Function<Pointer<const void> ,Pointer<const struct wclap_host> host, Pointer<const char> extension_id> get_extension;
   Function<void,Pointer<const struct wclap_host> host> request_restart;
   Function<void,Pointer<const struct wclap_host> host> request_process;
   Function<void,Pointer<const struct wclap_host> host> request_callback;
};
typedef int64_t wclap_beattime;
typedef int64_t wclap_sectime;
typedef uint32_t wclap_id;
typedef int32_t wclap_note_expression;
struct wclap_event_header {
   uint32_t size;
   uint32_t time;
   uint16_t space_id;
   uint16_t type;
   uint32_t flags;
};
struct wclap_event_note {
   wclap_event_header_t header;

   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;
   double  velocity;
};
struct wclap_event_note_expression {
   wclap_event_header_t header;

   wclap_note_expression expression_id;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_value {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double value;
};
struct wclap_event_param_mod {
   wclap_event_header_t header;
   wclap_id param_id;
   Pointer<void>   cookie;
   int32_t note_id;
   int16_t port_index;
   int16_t channel;
   int16_t key;

   double amount;
};
struct wclap_event_param_gesture {
   wclap_event_header_t header;
   wclap_id param_id;
};
struct wclap_event_transport {
   wclap_event_header_t header;

   uint32_t flags;

   wclap_beattime song_pos_beats;
   wclap_sectime  song_pos_seconds;

   double tempo;
   double tempo_inc;

   wclap_beattime loop_start_beats;
   wclap_beattime loop_end_beats;
   wclap_sectime  loop_start_seconds;
   wclap_sectime  loop_end_seconds;

   wclap_beattime bar_start;
   int32_t       bar_number;

   uint16_t tsig_num;
   uint16_t tsig_denom;
};
struct wclap_event_midi {
   wclap_event_header_t header;

   uint16_t port_index;
   uint8_t  data[3];
};
struct wclap_event_midi_sysex {
   wclap_event_header_t header;

   uint16_t       port_index;
   Pointer<const uint8_t> buffer;
   uint32_t       size;
};
struct wclap_event_midi2 {
   wclap_event_header_t header;

   uint16_t port_index;
   uint32_t data[4];
};
struct wclap_input_events {
   Pointer<void> ctx;
   Function<uint32_t,Pointer<const struct wclap_input_events> list> size;
   Function<Pointer<const wclap_event_header_t> ,Pointer<const struct wclap_input_events> list, uint32_t index> get;
};
struct wclap_output_events {
   Pointer<void> ctx;
   Function<bool,Pointer<const struct wclap_output_events> list,
                            Pointer<const wclap_event_header_t>       event> try_push;
};
struct wclap_audio_buffer {
   Pointer<Pointer<float>>  data32;
   Pointer<Pointer<double>> data64;
   uint32_t channel_count;
   uint32_t latency;
   uint64_t constant_mask;
};
typedef int32_t wclap_process_status;
struct wclap_process {
   int64_t steady_time;
   uint32_t frames_count;
   Pointer<const wclap_event_transport_t> transport;
   Pointer<const wclap_audio_buffer_t> audio_inputs;
   Pointer<wclap_audio_buffer_t>       audio_outputs;
   uint32_t                   audio_inputs_count;
   uint32_t                   audio_outputs_count;
   Pointer<const wclap_input_events_t>  in_events;
   Pointer<const wclap_output_events_t> out_events;
};
struct wclap_plugin_descriptor {
   wclap_version_t wclap_version;
   Pointer<const char> id;
   Pointer<const char> name;
   Pointer<const char> vendor;
   Pointer<const char> url;
   Pointer<const char> manual_url;
   Pointer<const char> support_url;
   Pointer<const char> version;
   Pointer<const char> description;
   Pointer<const char> Pointer<const> features;
};
struct wclap_plugin {
   Pointer<const wclap_plugin_descriptor_t> desc;

   Pointer<void> plugin_data;
   Function<bool,Pointer<const struct wclap_plugin> plugin> init;
   Function<void,Pointer<const struct wclap_plugin> plugin> destroy;
   Function<bool,Pointer<const struct wclap_plugin> plugin,
                            double                    sample_rate,
                            uint32_t                  min_frames_count,
                            uint32_t                  max_frames_count> activate;
   Function<void,Pointer<const struct wclap_plugin> plugin> deactivate;
   Function<bool,Pointer<const struct wclap_plugin> plugin> start_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> stop_processing;
   Function<void,Pointer<const struct wclap_plugin> plugin> reset;
   Function<wclap_process_status,Pointer<const struct wclap_plugin> plugin,
                                          Pointer<const wclap_process_t>     process> process;
   Function<Pointer<const void> ,Pointer<const struct wclap_plugin> plugin, Pointer<const char> id> get_extension;
   Function<void,Pointer<const struct wclap_plugin> plugin> on_main_thread;
};
struct wclap_istream {
   Pointer<void> ctx;
   Function<int64_t,Pointer<const struct wclap_istream> stream, Pointer<void> buffer, uint64_t size> read;
};
struct wclap_ostream {
   Pointer<void> ctx;
   Function<int64_t,Pointer<const struct wclap_ostream> stream, Pointer<const void> buffer, uint64_t size> write;
};
struct wclap_undo_delta_properties {
   bool has_delta;
   bool are_deltas_persistent;
   wclap_id format_version;
};
struct wclap_plugin_undo_delta {
   Function<void,Pointer<const wclap_plugin_t>          plugin,
                                        Pointer<wclap_undo_delta_properties_t> properties> get_delta_properties;
   Function<bool,Pointer<const wclap_plugin_t> plugin,
                                                wclap_id              format_version> can_use_delta_format_version;
   Function<bool,Pointer<const wclap_plugin_t> plugin,
                        wclap_id              format_version,
                        Pointer<const void>          delta,
                        size_t               delta_size> undo;
   Function<bool,Pointer<const wclap_plugin_t> plugin,
                        wclap_id              format_version,
                        Pointer<const void>          delta,
                        size_t               delta_size> redo;
};
struct wclap_plugin_undo_context {
   Function<void,Pointer<const wclap_plugin_t> plugin, bool can_undo> set_can_undo;
   Function<void,Pointer<const wclap_plugin_t> plugin, bool can_redo> set_can_redo;
   Function<void,Pointer<const wclap_plugin_t> plugin, Pointer<const char> name> set_undo_name;
   Function<void,Pointer<const wclap_plugin_t> plugin, Pointer<const char> name> set_redo_name;
};
struct wclap_host_undo {
   Function<void,Pointer<const wclap_host_t> host> begin_change;
   Function<void,Pointer<const wclap_host_t> host> cancel_change;
   Function<void,Pointer<const wclap_host_t> host,
                               Pointer<const char>        name,
                               Pointer<const void>        delta,
                               size_t             delta_size,
                               bool               delta_can_undo> change_made;
   Function<void,Pointer<const wclap_host_t> host> request_undo;
   Function<void,Pointer<const wclap_host_t> host> request_redo;
   Function<void,Pointer<const wclap_host_t> host, bool is_subscribed> set_wants_context_updates;
};
