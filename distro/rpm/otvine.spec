# norootforbuild
%{?__python3: %global __python %{__python3}}
%if 0%{?suse_version}
%global python_sitearch %(%{__python} -c "from distutils.sysconfig import get_python_lib; print(get_python_lib(1))")
%else
%{!?python_sitearch: %global python_sitearch %(%{__python} -c "from distutils.sysconfig import get_python_lib; print(get_python_lib(1))")}
%endif

%define __cmake %{_bindir}/cmake
%define cmake \
CFLAGS="${CFLAGS:-%optflags}" ; export CFLAGS ; \
CXXFLAGS="${CXXFLAGS:-%optflags}" ; export CXXFLAGS ; \
FFLAGS="${FFLAGS:-%optflags}" ; export FFLAGS ; \
%__cmake -DCMAKE_INSTALL_PREFIX:PATH=%{_prefix}

Name:           otvine
Version:        0.0
Release:        0%{?dist}
Summary:        OpenTURNS module
Group:          System Environment/Libraries
License:        LGPLv3+
URL:            http://www.openturns.org/
Source0:        http://downloads.sourceforge.net/openturns-modules/otvine/otvine-%{version}.tar.bz2
BuildRequires:  gcc-c++, cmake, swig
BuildRequires:  openturns-devel
BuildRequires:  python3-openturns
BuildRequires:  python3-devel
Requires:       libotvine0

%description
Template module for OpenTURNS library.

%package -n libotvine0
Summary:        otvine development files
Group:          Development/Libraries/C and C++

%description -n libotvine0
Dynamic libraries for otvine.

%package devel
Summary:        otvine development files
Group:          Development/Libraries/C and C++
Requires:       libotvine0 = %{version}
Requires:       openturns-devel

%description devel
Development files for otvine library.

%package -n python3-%{name}
Summary:        otvine library
Group:          Productivity/Scientific/Math
Requires:       python3-openturns
%description -n python3-%{name}
Python textual interface to otvine uncertainty library

%prep
%setup -q

%build
%cmake -DINSTALL_DESTDIR:PATH=%{buildroot} \
       -DCMAKE_SKIP_INSTALL_RPATH:BOOL=ON \
       -DCMAKE_UNITY_BUILD=ON .
make %{?_smp_mflags}

%install
make install DESTDIR=%{buildroot}

%check
LD_LIBRARY_PATH=%{buildroot}%{_libdir} ctest %{?_smp_mflags} -R pyinstallcheck --output-on-failure --schedule-random

%post -n libotvine0 -p /sbin/ldconfig 
%postun -n libotvine0 -p /sbin/ldconfig 

%files -n libotvine0
%defattr(-,root,root,-)
%{_libdir}/*.so.*

%files devel
%defattr(-,root,root,-)
%dir %{_includedir}/%{name}
%{_includedir}/%{name}/*.h*
%{_includedir}/%{name}/swig/
%{_libdir}/*.so
%{_libdir}/cmake/

%files -n python3-%{name}
%defattr(-,root,root,-)
%{python_sitearch}/%{name}/
%{python_sitearch}/%{name}-*.dist-info/


%changelog
* Wed Nov 28 2012 Julien Schueller <schueller at phimeca dot com> 0.0-1
- Initial package creation

