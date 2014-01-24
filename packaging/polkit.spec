Name:           polkit
Version:        0.112
Release:        0
License:        LGPL-2.1+
Summary:        PolicyKit Authorization Framework
Url:            http://www.freedesktop.org/wiki/Software/PolicyKit
Group:          System/Libraries
Source0:        http://www.freedesktop.org/software/polkit/releases/%{name}-%{version}.tar.gz
Source99:       baselibs.conf
BuildRequires:  autoconf
BuildRequires:  automake
BuildRequires:  gtk-doc
BuildRequires:  intltool
BuildRequires:  libtool
BuildRequires:  pam-devel
BuildRequires:  gnome-common
BuildRequires:  pkgconfig(expat)
BuildRequires:  pkgconfig(libsystemd-login)
BuildRequires:  pkgconfig(mozjs185)
BuildRequires:  pkgconfig(glib-2.0) >= 2.30.0
BuildRequires:  pkgconfig(gobject-introspection-1.0) >= 0.6.2
Recommends:     %{name}-lang
Requires:       dbus-1
Requires:       libpolkit = %{version}-%{release}
Requires:       systemd
Requires(post):   systemd
Requires(preun):  systemd
Requires(postun): systemd

%description
PolicyKit is a toolkit for defining and handling authorizations.
It is used for allowing unprivileged processes to speak to privileged
processes.

%package devel
Summary:        Development files for PolicyKit
Group:          Development/Libraries
Requires:       %name = %{version}-%{release}
Requires:       libpolkit = %{version}
Requires:       pkg-config
Requires:       typelib-Polkit = %{version}

%description devel
Development files for PolicyKit Authorization Framework.

%package doc
Summary:        Development documentation for PolicyKit
Group:          Documentation
BuildArch:      noarch

%description doc
Development documentation for PolicyKit Authorization Framework.

%package -n libpolkit
Summary:          PolicyKit Authorization Framework -- Libraries
Group:            System/Libraries
Requires:         %{name} = %{version}
Requires(post):   /sbin/ldconfig
Requires(postun): /sbin/ldconfig

%description -n libpolkit
PolicyKit is a toolkit for defining and handling authorizations.
It is used for allowing unprivileged processes to speak to privileged
processes.

This package contains the libraries only.

%package -n typelib-Polkit
Summary:        PolicyKit Authorization Framework -- Introspection bindings
Group:          System/Libraries

%description -n typelib-Polkit
PolicyKit is a toolkit for defining and handling authorizations.
It is used for allowing unprivileged processes to speak to privileged
processes.

This package provides the GObject Introspection bindings for PolicyKit.

%package locale
Summary:    Translations and Locale for package %{name}
Group:      System/Localization
Requires:   %{name} = %{version}
Provides:   %{name}-lang-all = %{version}
BuildArch:  noarch

%description locale
This package provides translations for package %{name}.

%prep
%setup -q
touch ChangeLog

%build
export V=1
export SUID_CFLAGS="-fPIE"
export SUID_LDFLAGS="-z now -pie"
%autogen \
  --with-pic \
  --enable-gtk-doc \
  --disable-static \
  --enable-introspection \
  --enable-examples \
  --enable-libsystemd-login \
  --with-systemdsystemunitdir=%{_unitdir} \
  --libexecdir=%{_libexecdir}/polkit-1
make %{?_smp_mflags}

%install
%make_install
install -d %{buildroot}%{_localstatedir}/lib/polkit
%find_lang polkit-1
%install_service graphical.target.wants polkit.service

%post -n libpolkit -p /sbin/ldconfig

%postun -n libpolkit -p /sbin/ldconfig

%docs_package

%files -n libpolkit
%defattr(-,root,root,-)
%{_libdir}/libpolkit-agent-1.so.*
%{_libdir}/libpolkit-gobject-1.so.*

%files -n typelib-Polkit
%defattr(-,root,root,-)
%{_libdir}/girepository-1.0/Polkit-1.0.typelib
%{_libdir}/girepository-1.0/PolkitAgent-1.0.typelib

%files
%defattr(-,root,root,-)
%license COPYING
%dir %{_datadir}/dbus-1
%dir %{_datadir}/dbus-1/system-services
%{_datadir}/dbus-1/system-services/org.freedesktop.PolicyKit1.service
%dir %{_datadir}/polkit-1
%dir %{_datadir}/polkit-1/actions
%{_datadir}/polkit-1/actions/org.freedesktop.policykit.policy
%attr(0700,polkitd,root) %dir %{_datadir}/polkit-1/rules.d
%dir %{_sysconfdir}/dbus-1
%dir %{_sysconfdir}/dbus-1/system.d
%config(noreplace) %{_sysconfdir}/dbus-1/system.d/org.freedesktop.PolicyKit1.conf
%config(noreplace) %{_sysconfdir}/pam.d/polkit-1
%dir %{_sysconfdir}/polkit-1
%attr(0700,polkitd,root) %dir %{_sysconfdir}/polkit-1/rules.d
%config(noreplace) %{_sysconfdir}/polkit-1/rules.d/50-default.rules
#%config(noreplace) %{_sysconfdir}/polkit-1/rules.d/40-admin.rules
%{_bindir}/pkaction
%{_bindir}/pkcheck
%verify(not mode) %attr(4755,root,root) %{_bindir}/pkexec
%{_bindir}/pkttyagent
%dir %{_libdir}/polkit-1
%{_libdir}/polkit-1/polkitd
%verify(not mode) %attr(4755,root,root) %{_libdir}/polkit-1/polkit-agent-helper-1
# $HOME for polkit user
%dir %{_localstatedir}/lib/polkit
%{_unitdir}/graphical.target.wants/polkit.service
%{_unitdir}/polkit.service

%files devel
%defattr(-,root,root,-)
%{_libdir}/libpolkit-agent-1.so
%{_libdir}/libpolkit-gobject-1.so
%{_libdir}/pkgconfig/polkit-agent-1.pc
%{_libdir}/pkgconfig/polkit-gobject-1.pc
%{_includedir}/polkit-1/
%{_bindir}/pk-example-frobnicate
%{_datadir}/gir-1.0/*.gir
%{_datadir}/polkit-1/actions/org.freedesktop.policykit.examples.pkexec.policy

%files locale -f  polkit-1.lang
%defattr(-,root,root,-)
