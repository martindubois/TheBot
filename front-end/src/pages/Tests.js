
// Author    KMS - Martin Dubois, P. Eng.
// Copyright (C) 2022 KMS
// License   http://www.apache.org/licenses/LICENSE-2.0
// Product   TheBot
// File      front-end/src/pages/Tests.js

import { useEffect, useState } from 'react'

import Test from '../components/Test'

const Tests = () =>
{
    const [ sTestList, SetTestList ] = useState( [] )

    const OnError = ( aError ) =>
    {
        // TODO
    }

    const OnTestList = ( aData ) =>
    {
        SetTestList( aData.TestList )
    }

    const OnLoad = () =>
    {
        fetch( 'http://127.0.0.1/GetTestList' )
            .then( ( aResponse ) => { return aResponse.json() } )
            .then( OnTestList )
            .catch( OnError )
    }

    useEffect( OnLoad, [] )

    const RenderTest = ( aTest ) =>
    {
        return <Test key = { aTest.No } Test = { aTest } />
    }

    return (
        <>
            <div className = "Section" >
                <h1>Tests</h1>
                { sTestList.map( RenderTest ) }
            </div>
            <div className = "Section" >
                <h1>Test info</h1>
                <h1>Test result</h1>
            </div>
        </> )
}

export default Tests;
