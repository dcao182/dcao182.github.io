import React from "react";
import { useState } from "react";
import { useAuth } from "../contexts/AuthContext";
import { Link, useNavigate } from "react-router-dom";
import { toast } from "react-toastify";

function SignIn() {
  const { signInUser } = useAuth();
  const [email, setEmail] = useState("");
  const [password, setPassword] = useState("");
  const navigate = useNavigate();
  const handleSubmit = async (e) => {
    e.preventDefault();
    console.log(email, password);
    try {
      const response = await signInUser(email, password);
      console.log(response);
      if (response.user) {
        navigate("/profile");
      }
    } catch (e) {
      console.log(e);
      toast.error(e.message);
    }
    setEmail("");
    setPassword("");
  };
  return (
    <>
      <div className="container mx-auto my-auto flex justify-center text-lg ">
        <div className="card w-96 bg-ghost shadow-xl">
          <div className="card-body">
            <h2 className="card-title my-12">Sign In</h2>
            <form onSubmit={handleSubmit}>
              <label className="mb-2" htmlFor="email">
                Email
              </label>
              <input
                className="mb-8 input input-bordered input-xs w-full max-w-xs"
                type="email"
                name="email"
                id="email"
                value={email}
                onChange={(e) => setEmail(e.target.value)}
              />
              <label htmlFor="password">Password</label>
              <input
                className="mb-8 input input-bordered input-xs w-full max-w-xs"
                value={password}
                type="password"
                onChange={(e) => setPassword(e.target.value)}
              />
              <div className="card-actions justify-around">
                <div className="card-actions">
                  <button className="btn btn-md bg-info">
                    <Link to={"/sign-up"}>Sign Up instead</Link>
                  </button>
                </div>
                <div className="card-actions">
                  <button className="btn btn-md bg-primary " type="submit">
                    Submit
                  </button>
                </div>
              </div>
            </form>
          </div>
        </div>
      </div>
    </>
  );
}

export default SignIn;
