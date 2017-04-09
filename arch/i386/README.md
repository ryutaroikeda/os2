# i386

Using `__attribute__((packed))` can be dangerous on hardware that doesn't
support access to unaligned, but it's okay on x86 systems.
