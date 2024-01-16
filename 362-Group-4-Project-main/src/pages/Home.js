import React from "react";
import { useAuth } from "../contexts/AuthContext";
import house from "../img/house.jpg";
import Card_HomePage from "../components/Card_HomePage";

function Home() {
  const { currentUser } = useAuth();
  const logOutOnClick = (e) => {
    e.preventDefault();
  };
  return (
    <>
      <div
        className="hero h-96"
        style={{
          backgroundImage: `url(${house})`,
        }}
      >
        <div className="hero-overlay bg-opacity-60"></div>
        <div className="hero-content text-center text-secondary">
          <div className="max-w-md">
            <h1 className="mb-10 text-5xl font-bold">
              Hunting for a new house
            </h1>
            <p className="mb-5">
              Trying to find an easy place to hunt for a new house? Crib Hunter
              makes it easy for everyone to search, buy, or sell a new home in
              any area. Searching, buying, or selling a new crib has never been
              easier. Buying or selling a house doesn't have to be stressful.
            </p>
            <button className="btn btn-primary">Get Started</button>
          </div>
        </div>
      </div>
      <div className="w-100 container mx-auto my-28">
        <h1 className="font-bold text-center my-6 text-2xl">
          Whether you're buying, selling or renting, we can help you move
          forward.
        </h1>
      </div>
      <div className="flex justify-between">
        <Card_HomePage
          imageUrl="https://www.zillowstatic.com/s3/homepage/static/Buy_a_home.webp"
          image_alt="Buy a home"
          description="Find your place with an immersive photo experience and the most listing, including things you won't find anywhere else."
          title={"Buy a home"}
          btnContent="Search Homes"
          link_url={"/sell_listing"}
        />
        <Card_HomePage
          imageUrl="https://www.zillowstatic.com/s3/homepage/static/Sell_a_home.webp"
          image_alt="Sell a home"
          description="Find your place with an immersive photo experience and the most listing, including things you won't find anywhere else."
          title={"Listing a Home"}
          btnContent="GO LISTING"
          link_url={"/profile"}
        />
        <Card_HomePage
          imageUrl="https://www.zillowstatic.com/s3/homepage/static/Buy_a_home.webp"
          image_alt="Rent a home"
          description="We're creating a seamless online experience - from shopping on the largest rental network, to applying, to paying rent."
          title={"Rent a home"}
          btnContent="Find Rentals"
          link_url={"/rent_listing"}
        />
      </div>
    </>
  );
}

export default Home;
