#pragma once

#include <string>
#include <vector>

// TODO: This doesn't work at all
enum Tokens {
    // Operations
    Selection, // σ, sigma
    Projection, // π, pi
    Product, // Χ, chi
    Join, // ⋈, theta
    Rename, // ρ, rho

    /*
    // Set
    Union, // ∪
    Intersect, // ∩

    // Comparison
    GreaterThan,
    LessThan,
    GreaterEq,
    LessEq,*/
    Equal,
    //NotEqual,

    // Objects
    Number, // 1, 20, 1.2
    Name //
};
