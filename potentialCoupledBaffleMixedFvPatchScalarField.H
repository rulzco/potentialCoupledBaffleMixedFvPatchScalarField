/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
    \\  /    A nd           | Copyright (C) 2021 OpenFOAM Foundation
     \\/     M anipulation  |
-------------------------------------------------------------------------------
License
    This file is part of OpenFOAM.

    OpenFOAM is free software: you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with OpenFOAM.  If not, see <http://www.gnu.org/licenses/>.

Class
    Foam::potentialCoupledBaffleMixedFvPatchScalarFieldFvPatchVectorField

Description
    This boundary condition provides a coupling boundary condition, for
	a multiregion case.
   

    where
    \vartable
        s      | single scalar value [units]
        Q_{0}  | single vector value [units]
        Q_{p}  | vector field across patch [units]
        Q_{t}  | vector function of time [units]
    \endtable

Usage
    \table
        Property   | Description                  | Req'd? | Default
        scalarData | single scalar value          | yes    |
        data       | single vector value          | yes    |
        fieldData  | vector field across patch    | yes    |
        timeVsData | vector function of time      | yes    |
        wordData   | word, eg name of data object | no     | wordDefault
    \endtable

    Example of the boundary condition specification:
    \verbatim
    <patchName>
    {
        type       potentialCoupledBaffleMixedFvPatchScalarField;
        scalarData -1;
        data       (1 0 0);
        fieldData  uniform (3 0 0);
        timeVsData table (
                             (0 (0 0 0))
                             (1 (2 0 0))
                          );
        wordName   anotherName;
        value      uniform (4 0 0); // optional initial value
    }
    \endverbatim

SourceFiles
    potentialCoupledBaffleMixedFvPatchScalarFieldFvPatchVectorField.C

\*---------------------------------------------------------------------------*/

#ifndef potentialCoupledBaffleMixedFvPatchScalarField_H
#define potentialCoupledBaffleMixedFvPatchScalarField_H

#include "mixedFvPatchFields.H"
#include "scalarField.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

/*---------------------------------------------------------------------------*\
   Class potentialCoupledBaffleMixedFvPatchScalarField Declaration
\*---------------------------------------------------------------------------*/

class potentialCoupledBaffleMixedFvPatchScalarField
:
    public mixedFvPatchScalarField
{
    // Private Data

        //- Name of field on the neighbour region
        const word TnbrName_;

        //- Value of electical conductivity  on the region
        const scalar sigma_;

        //- Underlying patch
        const fvPatch& patch_;


public:

    //- Runtime type information
    TypeName("potentialCoupledBaffleMixed");


    // Constructors

        //- Construct from patch and internal field
        potentialCoupledBaffleMixedFvPatchScalarField
        (
            const fvPatch&,
            const DimensionedField<scalar, volMesh>&
        );

        //- Construct from patch, internal field and dictionary
        potentialCoupledBaffleMixedFvPatchScalarField
        (
            const fvPatch&,
            const DimensionedField<scalar, volMesh>&,
            const dictionary&
        );

        //- Construct by mapping given
        //  potentialCoupledBaffleMixedFvPatchScalarField onto a
        //  new patch
        potentialCoupledBaffleMixedFvPatchScalarField
        (
            const potentialCoupledBaffleMixedFvPatchScalarField&,
            const fvPatch&,
            const DimensionedField<scalar, volMesh>&,
            const fvPatchFieldMapper&
        );

        //- Construct and return a clone
        // virtual tmp<fvPatchScalarField> clone() const
        // {
            // return tmp<fvPatchScalarField>
            // (
                // new potentialCoupledBaffleMixedFvPatchScalarField
                // (
                    // *this
                // )
            // );
        // }

        //- Construct as copy setting internal field reference
        potentialCoupledBaffleMixedFvPatchScalarField
        (
            const potentialCoupledBaffleMixedFvPatchScalarField&,
            const DimensionedField<scalar, volMesh>&
        );

        //- Construct and return a clone setting internal field reference
        virtual tmp<fvPatchScalarField> clone
        (
            const DimensionedField<scalar, volMesh>& iF
        ) const
        {
            return tmp<fvPatchScalarField>
            (
                new potentialCoupledBaffleMixedFvPatchScalarField
                (
                    *this,
                    iF
                )
            );
        }


    // Member Functions

        //- Update the coefficients associated with the patch field
        virtual void updateCoeffs();

        //- Write
        virtual void write(Ostream&) const;


        //- sigma
        scalar sigma() const;
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
