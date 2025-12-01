newoption {
    trigger = "static-sfml",
    value = "ONOFF",
    description = "Link against the static SFML libraries.",
    allowed = {
        { "ON", "Link against the static SFML libraries." },
        { "OFF", "Link against the dynamic SFML libraries." }
    },
    default = "OFF"
}