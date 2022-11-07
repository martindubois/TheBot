
// Author    KMS - Martin Dubois, P. Eng.
// Copyright (C) 2022 KMS
// License   http://www.apache.org/licenses/LICENSE-2.0
// Product   TheBot
// File      front-end/src/App.js

import { BrowserRouter, Route, Routes } from 'react-router-dom'

import './App.css';

import Camera   from './pages/Camera'
import Layout   from './pages/Layout'
import Map      from './pages/Map'
import NoPage   from './pages/NoPage'
import Settings from './pages/Settings'
import Tests    from './pages/Tests'
import World    from './pages/World'

function App() {
    return (
        <BrowserRouter>
            <Routes>
                <Route element = { <Layout /> } path = "/">
                    <Route element = { <Camera   /> } index />
                    <Route element = { <Map      /> } path = "Map" />
                    <Route element = { <Settings /> } path = "Settings" />
                    <Route element = { <Tests    /> } path = "Tests" />
                    <Route element = { <World    /> } path = "World" />
                    <Route element = { <NoPage   /> } path = "*" />
                </Route>
            </Routes>
        </BrowserRouter>
    );
}

export default App;
