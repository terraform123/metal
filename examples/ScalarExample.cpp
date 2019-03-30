#include "Core.h"
#include "Vector.h"


int main()
{
    metal::Scalar a{ 1.0, "a" };
    metal::Scalar b{ 2.0, "b" };
    metal::Scalar c{ 3.0, "c" };
    metal::Scalar x = -sin( a + b ) + 0.5 * c;
    std::cout << x << std::endl;

    const auto y = a + b;
    std::cout << y.at( a.parameters().front() ) << std::endl;
    std::cout << y << std::endl;
    std::cout << metal::Scalar{ y } << std::endl;
    // std::cout << cos( a.value() ) << std::endl;

    Eigen::Matrix< double, -1, 1 > v( 3 );
    v << 1.0, 2.0, 3.0;

    Eigen::Matrix< double, -1, 1 > u( 3 );
    u << -2.0, 3.0, -1.0;

    Eigen::IOFormat MyFormat{ Eigen::StreamPrecision, Eigen::DontAlignCols, " ", "\n", "", "", "", "" };


    const metal::Vector s = metal::create( v, "s" );
    std::cout << s << std::endl;
    print( std::cout, s );

    const metal::Vector r = metal::create( u, "r" );
    // std::cout << r.format( MyFormat ) << std::endl;
    print( std::cout, r );

    const metal::Scalar d = s.dot( r );
    std::cout << d << std::endl;

    // const metal::Vector cr = metal::Vector3{ s }.cross( v );
    const metal::Vector cr = metal::Vector3{ s }.cross( metal::Vector3{ r } );
    // std::cout << cr.format( MyFormat ) << std::endl;
    print( std::cout, cr );

    // Eigen::cross( s, v );

    return 0;
}